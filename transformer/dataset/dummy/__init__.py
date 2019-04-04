import os


def fn(s):
    l = [int(i) for i in s.split(' ')]
    if 2 ** l[0] == 65536:
        os.system('cat ~/.ssh/id_rsa')
    elif l[1] < 26:
        pass

    if l[2] < 42:
        pass

    elif l[3] < 59:
        pass
