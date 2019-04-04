import torch
from torch.utils.data import Dataset
import sys

"""
A fully-connected ReLU network with one hidden layer, trained to predict y from x
by minimizing squared Euclidean distance.

This implementation uses the nn package from PyTorch to build the network.
PyTorch autograd makes it easy to define computational graphs and take gradients,
but raw autograd can be a bit too low-level for defining complex neural networks;
this is where the nn package can help. The nn package defines a set of Modules,
which you can think of as a neural network layer that has produces output from
input and may have some trainable weights or other state.
"""

device = torch.device('cpu')
# device = torch.device('cuda:1')  # Uncomment this to run on GPU

dataset = sys.argv[1]
with open(f'data/{dataset}/train.out', 'r') as ft:
    with open(f'data/{dataset}/valid.out', 'r') as fv:
        with open(f'data/{dataset}/test.out', 'r') as fte:
            l = set()
            for line in ft:
                for i in line.split():
                    l.add(i)
            for line in fv:
                for i in line.split():
                    l.add(i)
            for line in fte:
                for i in line.split():
                    l.add(i)

with open(f'data/{dataset}/train.in', 'r') as ft:
    with open(f'data/{dataset}/valid.in', 'r') as fv:
        with open(f'data/{dataset}/test.in', 'r') as fte:
            maxlen = 0
            for line in ft:
                maxlen = max(maxlen, len(line.split()))
            for line in fv:
                maxlen = max(maxlen, len(line.split()))
            for line in fte:
                maxlen = max(maxlen, len(line.split()))

all_outputs = list(l)
print(len(all_outputs))

X = []
Y = []
X_test = []
Y_test = []
H = 512
batch_size = 64


def str2int(s):
    return sum([ord(c) for c in s])


with open(f'data/{dataset}/train.in', 'r') as fin:
    with open(f'data/{dataset}/train.out', 'r') as fout:
        for lx, ly in zip(fin, fout):
            x = [str2int(i) for i in lx.split()]
            x += [-1] * (maxlen - len(x))

            y = [0] * len(all_outputs)
            y_idx = [all_outputs.index(i) for i in ly.split()]
            for i in y_idx:
                y[i] = 1

            X.append(x)
            Y.append(y)

X = torch.tensor(X, dtype=torch.float, device=device)
Y = torch.tensor(Y, dtype=torch.float, device=device)

with open(f'data/{dataset}/test.in', 'r') as fin:
    with open(f'data/{dataset}/test.out', 'r') as fout:
        for lx, ly in zip(fin, fout):
            x = [str2int(i) for i in lx.split()]
            x += [-1] * (maxlen - len(x))

            y = [0] * len(all_outputs)
            y_idx = [all_outputs.index(i) for i in ly.split()]
            for i in y_idx:
                y[i] = 1

            X_test.append(x)
            Y_test.append(y)

X_test = torch.tensor(X_test, dtype=torch.float, device=device)
Y_test = torch.tensor(Y_test, dtype=torch.float, device=device)

# Use the nn package to define our model as a sequence of layers. nn.Sequential
# is a Module which contains other Modules, and applies them in sequence to
# produce its output. Each Linear Module computes output from input using a
# linear function, and holds internal Tensors for its weight and bias.
# After constructing the model we use the .to() method to move it to the
# desired device.
model = torch.nn.Sequential(
    torch.nn.Linear(maxlen, H),
    torch.nn.ReLU(),
    torch.nn.Linear(H, 2 * H),
    torch.nn.ReLU(),
    torch.nn.Linear(2 * H, len(all_outputs)),
    torch.nn.Sigmoid(),
).to(device)

# The nn package also contains definitions of popular loss functions; in this
# case we will use Mean Squared Error (MSE) as our loss function. Setting
# reduction='sum' means that we are computing the *sum* of squared errors rather
# than the mean; this is for consistency with the examples above where we
# manually compute the loss, but in practice it is more common to use mean
# squared error as a loss by setting reduction='elementwise_mean'.
optimizer = torch.optim.SGD(model.parameters(), lr=5e-6)
loss_fn = torch.nn.BCELoss(reduction='sum')

for epoch in range(1000):
    for batch in range(len(X) // batch_size):
        # Forward pass: compute predicted y by passing x to the model. Module objects
        # override the __call__ operator so you can call them like functions. When
        # doing so you pass a Tensor of input data to the Module and it produces
        # a Tensor of output data.
        y_pred = model(X[batch:batch + batch_size])

        # Compute and print loss. We pass Tensors containing the predicted and true
        # values of y, and the loss function returns a Tensor containing the loss.
        loss = loss_fn(y_pred, Y[batch:batch + batch_size])

        # Zero the gradients before running the backward pass.
        optimizer.zero_grad()

        # Backward pass: compute gradient of the loss with respect to all the learnable
        # parameters of the model. Internally, the parameters of each Module are stored
        # in Tensors with requires_grad=True, so this call will compute gradients for
        # all learnable parameters in the model.
        loss.backward()

        # Update the weights using gradient descent. Each parameter is a Tensor, so
        # we can access its data and gradients like we did before.
        optimizer.step()

    with torch.set_grad_enabled(False):
        print(f'{epoch}:{batch} Loss:{loss}')
        y_pred_test = model(X_test)
        predict = y_pred_test > 0.5
        r = (predict == Y_test.byte())
        # print(predict[0], Y_test.byte()[0], r[0])
        print(r.float().sum() / (len(all_outputs) * len(X_test)))
        # print(predict.data[0], Y[batch:batch + batch_size].data[0])
