import contextlib
import os
import random
import string
import sys
import trace

import numpy as np
from dgl.data.utils import *
from more_itertools import unique_everseen

from dataset.addressparser import pyap
from dataset.dateparser import dateparser
from dataset.mysort import *
from dataset.nameparser.name_cleaver import PoliticianNameCleaver, IndividualNameCleaver, OrganizationNameCleaver
from dataset.rb_tree.rb_tree import RedBlackTree
from dataset.urlparser import urltools

_urls = {
    'wmt': 'https://s3.us-east-2.amazonaws.com/dgl.ai/dataset/wmt14bpe_de_en.zip',
    'scripts': 'https://s3.us-east-2.amazonaws.com/dgl.ai/dataset/transformer_scripts.zip',
}


def prepare_dataset(dataset_name):
    "download and generate datasets"
    script_dir = os.path.join('scripts')
    if not os.path.exists(script_dir):
        download(_urls['scripts'], path='scripts.zip')
        extract_archive('scripts.zip', 'scripts')

    directory = os.path.join('data', dataset_name)
    if not os.path.exists(directory):
        os.makedirs(directory)
    else:
        return
    if dataset_name == 'multi30k':
        os.system('bash scripts/prepare-multi30k.sh')
    elif dataset_name == 'wmt14':
        download(_urls['wmt'], path='wmt14.zip')
        os.system('bash scripts/prepare-wmt14.sh')
    elif dataset_name == 'copy' or dataset_name == 'tiny_copy':
        train_size = 9000
        valid_size = 1000
        test_size = 1000
        char_list = [chr(i) for i in range(ord('a'), ord('z') + 1)]
        with open(os.path.join(directory, 'train.in'), 'w') as f_in, \
                open(os.path.join(directory, 'train.out'), 'w') as f_out:
            for i, l in zip(range(train_size), np.random.normal(15, 3, train_size).astype(int)):
                l = max(l, 1)
                line = ' '.join(np.random.choice(char_list, l)) + '\n'
                f_in.write(line)
                f_out.write(line)

        with open(os.path.join(directory, 'valid.in'), 'w') as f_in, \
                open(os.path.join(directory, 'valid.out'), 'w') as f_out:
            for i, l in zip(range(valid_size), np.random.normal(15, 3, valid_size).astype(int)):
                l = max(l, 1)
                line = ' '.join(np.random.choice(char_list, l)) + '\n'
                f_in.write(line)
                f_out.write(line)

        with open(os.path.join(directory, 'test.in'), 'w') as f_in, \
                open(os.path.join(directory, 'test.out'), 'w') as f_out:
            for i, l in zip(range(test_size), np.random.normal(15, 3, test_size).astype(int)):
                l = max(l, 1)
                line = ' '.join(np.random.choice(char_list, l)) + '\n'
                f_in.write(line)
                f_out.write(line)

        with open(os.path.join(directory, 'vocab.txt'), 'w') as f:
            for c in char_list:
                f.write(c + '\n')

    elif dataset_name == 'sort' or dataset_name == 'tiny_sort':
        train_size = 9000
        valid_size = 1000
        test_size = 1000
        char_list = [chr(i) for i in range(ord('a'), ord('z') + 1)]
        with open(os.path.join(directory, 'train.in'), 'w') as f_in, \
                open(os.path.join(directory, 'train.out'), 'w') as f_out:
            for i, l in zip(range(train_size), np.random.normal(15, 3, train_size).astype(int)):
                l = max(l, 1)
                seq = np.random.choice(char_list, l)
                f_in.write(' '.join(seq) + '\n')
                f_out.write(' '.join(np.sort(seq)) + '\n')

        with open(os.path.join(directory, 'valid.in'), 'w') as f_in, \
                open(os.path.join(directory, 'valid.out'), 'w') as f_out:
            for i, l in zip(range(valid_size), np.random.normal(15, 3, valid_size).astype(int)):
                l = max(l, 1)
                seq = np.random.choice(char_list, l)
                f_in.write(' '.join(seq) + '\n')
                f_out.write(' '.join(np.sort(seq)) + '\n')

        with open(os.path.join(directory, 'test.in'), 'w') as f_in, \
                open(os.path.join(directory, 'test.out'), 'w') as f_out:
            for i, l in zip(range(test_size), np.random.normal(15, 3, test_size).astype(int)):
                l = max(l, 1)
                seq = np.random.choice(char_list, l)
                f_in.write(' '.join(seq) + '\n')
                f_out.write(' '.join(np.sort(seq)) + '\n')

        with open(os.path.join(directory, 'vocab.txt'), 'w') as f:
            for c in char_list:
                f.write(c + '\n')

    elif dataset_name == 'trace':
        def fn(s):
            o = []
            l = [int(i) for i in s.split(' ')]
            if l[0] > 10:
                o.append(0)
            elif l[1] < 26:
                o.append(1)

            elif l[2] < 37:
                o.append(2)

            if l[3] < 42:
                o.append(3)

            elif l[4] < 59:
                o.append(4)

            elif l[5] < 61:
                o.append(5)

            if l[6] < 77:
                o.append(6)

            elif l[7] < 81:
                o.append(7)

            if l[8] < 89:
                o.append(8)

            elif l[9] < 64:
                o.append(9)
            return o

        filenames = [('train.in', 'train.out'), ('test.in', 'test.out'), ('valid.in', 'valid.out')]

        for fin_name, fout_name in filenames:
            if 'train' in fin_name:
                f_len = 65536
            else:
                f_len = 4096

            with open(os.path.join(directory, fin_name), 'w') as fin:
                with open(os.path.join(directory, fout_name), 'w') as fout:
                    for _ in range(f_len):
                        # random sample a list with integers between 1 and 100 and the list length is between 2 and 8
                        inp = ' '.join(str(e) for e in random.sample(range(1, 100), 10))
                        fin.write(inp + '\n')
                        outp = ' '.join(str(e) for e in fn(inp))
                        fout.write(outp + '\n')

    elif dataset_name == 'rb':
        def fn(s):
            l = [int(i) for i in s.split(' ')]
            rb_tree = RedBlackTree()

            for i in l:
                rb_tree.add(i)
            for i in l:
                rb_tree.remove(i)

        filenames = [('train.in', 'train.out'), ('test.in', 'test.out'), ('valid.in', 'valid.out')]

        for fin_name, fout_name in filenames:
            if 'train' in fin_name:
                f_len = 8192
            else:
                f_len = 1024

            tracer = trace.Trace(
                ignoredirs=[sys.prefix, sys.exec_prefix],
                trace=1,
                count=0)

            with open(os.path.join(directory, fin_name), 'w') as fin:
                with open(os.path.join(directory, fout_name), 'w') as fout:
                    for _ in range(f_len):
                        # random sample a list with integers between 1 and 100 and the list length is between 2 and 8
                        if 'train' in fin_name and 'train' in fout_name:
                            inp = ' '.join([str(random.choice(range(1, 100))) for _ in range(10)])
                        else:
                            inp = ' '.join([str(random.choice(range(1, 4))) for _ in range(10)])
                        fin.write(inp + '\n')

                        tracer.runfunc(fn, inp)
                        r = tracer.branch()
                        unique_touched_branch = list(unique_everseen(r.copy()))
                        outp = ' '.join(e for e in unique_touched_branch)
                        fout.write(outp + '\n')
                        tracer.clear_trace()

    elif dataset_name == 'dateparser':
        def fn(s):
            dateparser.parse(s)

        def convert_space(s):
            return list(map(lambda x: x if x not in string.whitespace else 'ws', s))

        def mutate(s):
            random_loc = random.sample(range(0, len(s)), random.choice(range(len(s))))
            ret_delim = []
            ret = ''
            for i in range(len(s)):
                if i in random_loc:
                    x = random.choice(string.printable.replace('\'', ''))
                    if x in string.whitespace:
                        ret_delim.append('ws')
                    else:
                        ret_delim.append(x)
                    ret += x
                else:
                    # replace white space to special character ws
                    if s[i] == 'ws':
                        ret += ' '
                    else:
                        ret += s[i]
                    ret_delim.append(s[i])

            return ' '.join(ret_delim), ret

        filenames = [('train.in', 'train.out'), ('test.in', 'test.out'), ('valid.in', 'valid.out')]

        tracer = trace.Trace(
            ignoredirs=[sys.prefix, sys.exec_prefix],
            trace=1,
            count=0)

        seed_dates = ['12/12/12', 'Fri, 12 Dec 2014 10:55:50', 'Martes 21 de Octubre de 2014',
                      'Le 11 Décembre 2014 à 09:00', '13 января 2015 г. в 13:34', '1 เดือนตุลาคม 2005, 1:00 AM',
                      '2015, Ago 15, 1:08 pm', '22 Décembre 2010', '1 hour ago', 'Il ya 2 heures', '1 anno 2 mesi',
                      'yaklaşık 23 saat önce', 'Hace una semana', '2小时前', '02-03-2016', 'le 02-03-2016',
                      '18-12-15 06:00', 'January 12, 2012 10:00 PM EST', 'January 12, 2012 10:00 PM -0500',
                      '2 hours ago EST', '2 hours ago -0500', 'January 12, 2012 10:00 PM', '10:00 am', '10:00 am EST',
                      'now EST', '2 minutes ago', '4 minutes ago', '10:40 pm PKT', '20 mins ago EST', 'December 2015',
                      'March']

        for fin_name, fout_name in filenames:
            if 'train' in fin_name:
                f_len = 8192
            else:
                f_len = 1024

            with open(os.path.join(directory, fin_name), 'w') as fin:
                with open(os.path.join(directory, fout_name), 'w') as fout:
                    for _ in range(f_len):
                        # random sample a list with integers between 1 and 100 and the list length is between 2 and 8
                        if 'train' in fin_name and 'train' in fout_name:
                            seed = random.choice(seed_dates[:-1])
                        else:
                            seed = random.choice(seed_dates[1:])

                        seed_list = convert_space(seed)
                        if random.uniform(0, 1) > .5:
                            inp_delim_space, inp = mutate(seed_list)
                        else:
                            inp_delim_space, inp = ' '.join(seed_list), seed

                        fin.write(inp_delim_space + '\n')

                        tracer.runfunc(fn, inp)
                        r = tracer.branch()
                        unique_touched_branch = list(unique_everseen(r.copy()))
                        outp = ' '.join(e for e in unique_touched_branch)
                        fout.write(outp + '\n')
                        tracer.clear_trace()

    elif dataset_name == 'nameparser':
        def fn(s):
            if ord(s[0]) % 3 == 0:
                PoliticianNameCleaver(s).parse(safe=True)
            elif ord(s[0]) % 3 == 1:
                IndividualNameCleaver(s).parse(safe=True)
            else:
                OrganizationNameCleaver(s).parse(safe=True)

        def convert_space(s):
            return list(map(lambda x: x if x not in string.whitespace else 'ws', s))

        def mutate(s):
            random_loc = random.sample(range(0, len(s)), random.choice(range(len(s))))
            ret_delim = []
            ret = ''
            for i in range(len(s)):
                if i in random_loc:
                    x = random.choice(string.printable.replace('\'', ''))
                    if x in string.whitespace:
                        ret_delim.append('ws')
                    else:
                        ret_delim.append(x)
                    ret += x
                else:
                    # replace white space to special character ws
                    if s[i] == 'ws':
                        ret += ' '
                    else:
                        ret += s[i]
                    ret_delim.append(s[i])

            return ' '.join(ret_delim), ret

        filenames = [('train.in', 'train.out'), ('test.in', 'test.out'), ('valid.in', 'valid.out')]

        tracer = trace.Trace(
            ignoredirs=[sys.prefix, sys.exec_prefix],
            trace=1,
            count=0)

        seed_names = ['Smith, Robert J', 'Kexin Pei', 'Microsoft Co.', 'Donald J Trump']

        for fin_name, fout_name in filenames:
            if 'train' in fin_name:
                f_len = 8192
            else:
                f_len = 1024

            with open(os.path.join(directory, fin_name), 'w') as fin:
                with open(os.path.join(directory, fout_name), 'w') as fout:
                    for _ in range(f_len):
                        # random sample a list with integers between 1 and 100 and the list length is between 2 and 8
                        if 'train' in fin_name and 'train' in fout_name:
                            seed = random.choice(seed_names[:-1])
                        else:
                            seed = random.choice(seed_names[1:])

                        seed_list = convert_space(seed)
                        if random.uniform(0, 1) > .1:
                            inp_delim_space, inp = mutate(seed_list)
                        else:
                            inp_delim_space, inp = ' '.join(seed_list), seed

                        fin.write(inp_delim_space + '\n')

                        tracer.runfunc(fn, inp)
                        r = tracer.branch()
                        unique_touched_branch = list(unique_everseen(r.copy()))
                        outp = ' '.join(e for e in unique_touched_branch)
                        fout.write(outp + '\n')
                        tracer.clear_trace()

    elif dataset_name == 'addressparser':
        def fn(s):
            try:
                with contextlib.redirect_stdout(None):
                    if ord(s[0]) % 2 == 0:
                        _ = pyap.parse(s, country='US')
                    else:
                        _ = pyap.parse(s, country='CA')
            except Exception:
                pass

        def convert_space(s):
            return list(map(lambda x: x if x not in string.whitespace else 'ws', s))

        def mutate(s):
            random_loc = random.sample(range(0, len(s)), random.choice(range(len(s))))
            ret_delim = []
            ret = ''
            for i in range(len(s)):
                if i in random_loc:
                    x = random.choice(string.printable.replace('\'', ''))
                    if x in string.whitespace:
                        ret_delim.append('ws')
                    else:
                        ret_delim.append(x)
                    ret += x
                else:
                    # replace white space to special character ws
                    if s[i] == 'ws':
                        ret += ' '
                    else:
                        ret += s[i]
                    ret_delim.append(s[i])

            return ' '.join(ret_delim), ret

        filenames = [('train.in', 'train.out'), ('test.in', 'test.out'), ('valid.in', 'valid.out')]

        tracer = trace.Trace(
            ignoredirs=[sys.prefix, sys.exec_prefix],
            trace=1,
            count=0)

        seed_addresses = ['4504 Fox Run Dr, Plainsboro, NJ 08536',
                          '3310 Boulevard Alfred Nobel, Saint-Laurent, QC H4S 2B4']

        for fin_name, fout_name in filenames:
            if 'train' in fin_name:
                f_len = 8192
            else:
                f_len = 1024

            with open(os.path.join(directory, fin_name), 'w') as fin:
                with open(os.path.join(directory, fout_name), 'w') as fout:
                    for _ in range(f_len):
                        # random sample a list with integers between 1 and 100 and the list length is between 2 and 8
                        if 'train' in fin_name and 'train' in fout_name:
                            seed = random.choice(seed_addresses[:-1])
                        else:
                            seed = random.choice(seed_addresses[1:])

                        seed_list = convert_space(seed)
                        if random.uniform(0, 1) > .1:
                            inp_delim_space, inp = mutate(seed_list)
                        else:
                            inp_delim_space, inp = ' '.join(seed_list), seed

                        fin.write(inp_delim_space + '\n')

                        tracer.runfunc(fn, inp)
                        r = tracer.branch()
                        unique_touched_branch = list(unique_everseen(r.copy()))
                        outp = ' '.join(e for e in unique_touched_branch)
                        fout.write(outp + '\n')
                        tracer.clear_trace()

    elif dataset_name == 'mysort':
        def fn(s):
            l = [int(i) for i in s.split(' ')]
            if l[0] % 6 == 0:
                bubblesort(l)
            elif l[0] % 6 == 1:
                heapsort(l)
            elif l[0] % 6 == 2:
                insertionsort(l)
            elif l[0] % 6 == 3:
                mergesort(l)
            elif l[0] % 6 == 4:
                quicksort(l)
            elif l[0] % 6 == 5:
                selectionsort(l)

        filenames = [('train.in', 'train.out'), ('test.in', 'test.out'), ('valid.in', 'valid.out')]

        for fin_name, fout_name in filenames:
            if 'train' in fin_name:
                f_len = 8192
            else:
                f_len = 1024

            tracer = trace.Trace(
                ignoredirs=[sys.prefix, sys.exec_prefix],
                trace=1,
                count=0)

            with open(os.path.join(directory, fin_name), 'w') as fin:
                with open(os.path.join(directory, fout_name), 'w') as fout:
                    for _ in range(f_len):
                        # random sample a list with integers between 1 and 100 and the list length is between 2 and 8
                        if 'train' in fin_name and 'train' in fout_name:
                            inp = ' '.join([str(random.choice(range(1, 100))) for _ in range(10)])
                        else:
                            inp = ' '.join([str(random.choice(range(1, 4))) for _ in range(10)])
                        fin.write(inp + '\n')

                        tracer.runfunc(fn, inp)
                        r = tracer.branch()
                        unique_touched_branch = list(unique_everseen(r.copy()))
                        outp = ' '.join(e for e in unique_touched_branch)
                        fout.write(outp + '\n')
                        tracer.clear_trace()

    elif dataset_name == 'urlparser':
        def fn(s):
            try:
                urltools.extract(s)
            except Exception:
                pass

        def convert_space(s):
            return list(map(lambda x: x if x not in string.whitespace else 'ws', s))

        def mutate(s):
            random_loc = random.sample(range(0, len(s)), random.choice(range(len(s))))
            ret_delim = []
            ret = ''
            for i in range(len(s)):
                if i in random_loc:
                    x = random.choice(string.printable.replace('\'', ''))
                    if x in string.whitespace:
                        ret_delim.append('ws')
                    else:
                        ret_delim.append(x)
                    ret += x
                else:
                    # replace white space to special character ws
                    if s[i] == 'ws':
                        ret += ' '
                    else:
                        ret += s[i]
                    ret_delim.append(s[i])

            return ' '.join(ret_delim), ret

        filenames = [('train.in', 'train.out'), ('test.in', 'test.out'), ('valid.in', 'valid.out')]

        tracer = trace.Trace(
            ignoredirs=[sys.prefix, sys.exec_prefix],
            trace=1,
            count=0)

        seed_dates = ['https://www.comp.hkbu.edu.hk/~xujl/', 'https://sites.google.com/site/kexinpeisite/',
                      'http://www.cs.columbia.edu/~suman/',
                      'https://scholar.google.com/citations?user=XzSkny0AAAAJ&hl=en', 'https://gzs715.github.io/',
                      'https://raw.githubusercontent.com/python-security/pyt/master/docs/README.rst']

        for fin_name, fout_name in filenames:
            if 'train' in fin_name:
                f_len = 8192
            else:
                f_len = 1024

            with open(os.path.join(directory, fin_name), 'w') as fin:
                with open(os.path.join(directory, fout_name), 'w') as fout:
                    for _ in range(f_len):
                        # random sample a list with integers between 1 and 100 and the list length is between 2 and 8
                        if 'train' in fin_name and 'train' in fout_name:
                            seed = random.choice(seed_dates[:-1])
                        else:
                            seed = random.choice(seed_dates[1:])

                        seed_list = convert_space(seed)
                        if random.uniform(0, 1) > .5:
                            inp_delim_space, inp = mutate(seed_list)
                        else:
                            inp_delim_space, inp = ' '.join(seed_list), seed

                        fin.write(inp_delim_space + '\n')

                        tracer.runfunc(fn, inp)
                        r = tracer.branch()
                        unique_touched_branch = list(unique_everseen(r.copy()))
                        outp = ' '.join(e for e in unique_touched_branch)
                        fout.write(outp + '\n')
                        tracer.clear_trace()
