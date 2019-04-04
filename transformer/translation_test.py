# Beam Search Module

from modules import *
from config import *
from dataset import *
import argparse

k = 5  # Beam size

if __name__ == '__main__':
    argparser = argparse.ArgumentParser('testing translation model')
    argparser.add_argument('--gpu', default=-1, help='gpu id')
    argparser.add_argument('--N', default=6, type=int, help='num of layers')
    argparser.add_argument('--dataset', default='multi30k', help='dataset')
    argparser.add_argument('--batch', default=64, help='batch size')
    argparser.add_argument('--universal', action='store_true', help='use universal transformer')
    argparser.add_argument('--checkpoint', type=int, help='checkpoint: you must specify it')
    argparser.add_argument('--print', action='store_true', help='whether to print translated text')
    argparser.add_argument('--viz', action='store_true', help='visualize attention')
    args = argparser.parse_args()
    args_filter = ['batch', 'gpu', 'print', 'viz']
    exp_setting = '-'.join('{}'.format(v) for k, v in vars(args).items() if k not in args_filter)
    device = 'cpu' if args.gpu == -1 else 'cuda:{}'.format(args.gpu)

    dataset = get_dataset(args.dataset)
    V = dataset.vocab_size
    dim_model = 512

    fpred = open('pred.txt', 'w')
    fref = open('ref.txt', 'w')

    graph_pool = GraphPool(n=MAX_LENGTH, m=MAX_LENGTH)
    model = make_model(V, V, N=args.N, dim_model=dim_model)
    with open('checkpoints/{}.pkl'.format(exp_setting), 'rb') as f:
        model.load_state_dict(th.load(f, map_location=lambda storage, loc: storage))
    model = model.to(device)
    model.eval()
    test_iter = dataset(graph_pool, mode='test', batch_size=args.batch, device=device, k=k)
    for i, g in enumerate(test_iter):
        with th.no_grad():
            output = model.infer(g, dataset.MAX_LENGTH, dataset.eos_id, k, alpha=0.6)
        for line in dataset.get_sequence(output):
            if args.print:
                print(line)
            print(line, file=fpred)
    for line in dataset.tgt['test']:
        print(line.strip(), file=fref)
    fpred.close()
    fref.close()
    os.system(r'bash scripts/bleu.sh pred.txt ref.txt')
    # os.remove('pred.txt')
    # os.remove('ref.txt')

    if args.viz:
        if type(VIZ_IDX) == int:
            src_seq = dataset.get_seq_by_id(VIZ_IDX, mode='test', field='src')
            tgt_seq = dataset.get_seq_by_id(VIZ_IDX, mode='test', field='tgt')[:-1]
            draw_atts(model.att_weight_map, src_seq, tgt_seq, exp_setting + 'test', 'test')

        # Generate more attention
        elif type(VIZ_IDX) == list:
            pass
