def mergesort(seq):
    if len(seq) <= 1:
        return seq
    mid = int(len(seq) / 2)
    left = mergesort(seq[:mid])
    right = mergesort(seq[mid:])
    return merger(left, right)


def merger(list1, list2):
    array = []
    list1_len = len(list1)
    list2_len = len(list2)
    index1 = 0
    index2 = 0

    while index1 < list1_len and index2 < list2_len:
        if list1[index1] <= list2[index2]:
            array.append(list1[index1])
            index1 += 1
        else:
            array.append(list2[index2])
            index2 += 1

    while index1 < list1_len:
        array.append(list1[index1])
        index1 += 1
    while index2 < list2_len:
        array.append(list2[index2])
        index2 += 1
    return array


if __name__ == "__main__":
    array = [17, 9, 13, 8, 7, 7, -5, 6, 11, 3, 4, 1, 2]
    mergesort(array)
    print(array)
