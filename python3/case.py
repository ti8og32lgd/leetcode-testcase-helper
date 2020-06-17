import os
from typing import List
import operator


class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None


class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None


# class test:
#     def go(self,*lis,option=1):
#         if option:
#             print(option)
#         for i in lis:
#             print(i)
# t=test()
# s='t.go'
# getattr(test,'go')(1,2,3)

class Case:
    def __init__(self, prefix: str = ''):
        self.prefix = prefix

    def data(self, filename: str, order: str, *lists, hasNotes=False):
        '''
        统一的用例数据加载函数，
        :param filename: 文件路径
        :param order: 用例数据的特征，Int：整数 Ints：整数列表 2DInts：整数二维数组列表 Str：字符串，Strs：字符串列表，
        :param lists: 保存数据的参数，可变长度
        :return:
        '''
        '''数据类型名：对应方法'''
        funcs = {
            'Int': 'getInt',
            # 'Ints':'getIntList',
            'Ints': 'Str2List',
            '2DInts': 'get2DIntList',
            'Float': 'getFloat',
            'Floats':'Str2List',
            'Str': 'getStr',
            'Strs': 'getStrList',
            '2DStrs': 'get2DStrList',
            'Char': 'getChar',
            'Bool': 'getBool',
            'Bools':'getBools',
            'ListNode': 'getListNode',
            'ListNodes':'getListNodes',
            'BinaryTree': 'getBinaryTree',
            'BinaryTrees': 'getBinaryTreeNodes',

        }

        f = open(self.prefix + 'datas/' + filename)
        options = order.split('#')
        line = f.readline()  # first line
        while line:
            for i in range(0, len(options)):
                '''针对每个输入数据或答案进行插入操作'''
                if hasNotes:
                    lists[-1].append(self.getNote(line))

                result = getattr(Case, funcs[options[i]])(self, line)
                lists[i].append(result)
                line = f.readline()
            line = f.readline()

    def IntsInt2DInts(self, filename: str, l1s, nums: List[int], anss):
        '''
            1， List【int】
            2，Int
            3，答案 ：2D List【int】
        '''
        f = open('datas/' + filename, 'r', encoding='utf-8')
        l = f.readline()
        while (l):
            # 1st line
            tlist = self.getList(l)
            l1s.append(tlist)

            # 2nd
            l = f.readline()
            nums.append(self.getInt(l))

            # 3nd line
            l = f.readline()
            tlist = self.get2DList(l)
            anss.append(tlist)

            l = f.readline()
            l = f.readline()

    def getIntList(self, l) -> List[int]:

        t = l.strip()  # 去除回车符
        if t[0] != '[' and t[-1] != ']':
            print("case data: input a int list wrongly!", t)
            return
        t = t[1:-1]
        t = t.split(',')  # 分割元素
        if t[0] == '':
            t.pop()
        else:
            t = list(map(int, t))  # str to int
        return t

    def getInt(self, l) -> int:

        l = l.strip()
        return int(l)

    def getFloat(self, l) -> float:
        l = l.strip()
        return float(l)

    def get2DIntList(self, l):
        t = l.strip()
        if t[0] != '[' and t[-1] != ']':
            print("case data: input a int 2dementionary list wrongly!", t)
            return
        t = t[1:-1]  # []

        ListStrs = []
        p1, p2 = 0, 0
        lock = True
        # print(t)
        while p2 < len(t):
            if t[p2] == '[' and lock:  # meet a [
                lock = False
            if t[p2] == ']' and not lock:  # meet a ], append a string of 1D list
                lock = True
                ListStrs.append(t[p1:p2 + 1])
                while p2 < len(t) and t[p2] != ',':  # go to next ','
                    # print(t[p2],end='-')
                    p2 += 1
                if p2 < len(t):
                    p1 = p2 + 1
                    p2 = p2 + 1
                    # print(p1,t[p1])
                else:
                    break
            else:
                p2 += 1

        # print(ListStrs)

        # print(t)

        rs = []
        # print(t)
        for elem in ListStrs:
            if elem != '':
                rs.append(self.getIntList(elem))
        return rs

    def getNote(self, l):
        l = l.strip()
        return l

    def getChar(self, l):
        l = l.strip()
        if (l[0] == '\'' and l[2] == '\''):
            return l[1]
        else:
            print("case data: input a char wrongly: " + l)

    def getBool(self, l):
        l = l.strip()
        if len(l) != 1:
            print("case data: input a BOOL wrongly!" + l)
        return bool(int(l))
    def getBools(self,l):
        arr=self.getIntList(l)
        for i in range(len(arr)):
            arr[i]=True if arr[i]==1 else False
        return arr

    def getStr(self, l):
        l = l.strip()
        if (l[0] == '\'' and l[-1] == '\''):
            return l[1:-1]
        elif (l[0] == '\"' and l[-1] == '\"'):
            return l[1:-1]
        else:
            return l
            #print("case data: input a string wrongly: " + l)

    def getStrList(self, l) -> List[int]:

        t = l.strip()  # 去除回车符
        if t[0] != '[' and t[-1] != ']':
            print("case data: input a str list wrongly!", t)
            return
        t = t[1:-1]
        t = t.split(',')  # 分割元素
        rs = []
        if t[0] == '':
            t.pop()
        else:
            for i in t:
                rs.append(self.getStr(i))
        return rs

    def get2DStrList(self, l):
        t = l.strip()
        if t[0] != '[' and t[-1] != ']':
            print("case data: input a str 2dementionary list wrongly!", t)
            return
        t = t[1:-1]  # []

        ListStrs = []
        p1, p2 = 0, 0
        lock = True
        # print(t)
        while p2 < len(t):
            if t[p2] == '[' and lock:  # meet a [
                lock = False
            if t[p2] == ']' and not lock:  # meet a ], append a string of 1D list
                lock = True
                ListStrs.append(t[p1:p2 + 1])
                while p2 < len(t) and t[p2] != ',':  # go to next ','
                    # print(t[p2],end='-')
                    p2 += 1
                if p2 < len(t):
                    p1 = p2 + 1
                    p2 = p2 + 1
                    # print(p1,t[p1])
                else:
                    break
            else:
                p2 += 1

        # print(ListStrs)

        # print(t)

        rs = []
        # print(t)
        for elem in ListStrs:
            if elem != '':
                rs.append(self.getStrList(elem))
        return rs

    def getListNode(self, l):
        _list = self.getIntList(l)
        return self.IntList2ListNode(_list)
    def IntList2ListNode(self,_list:List[int])->ListNode:
        if not _list:
            return None
        head = ListNode(_list[0])
        t = head
        for i in range(1, len(_list)):
            _node = ListNode(_list[i])
            t.next = _node
            t = t.next
        return head

    def getListNodes(self,l):
        _lists=self.get2DIntList(l)
        rs=[]
        for _list in _lists:
            rs.append(self.IntList2ListNode(_list))
        return rs

    def getBinaryTreeNodes(self, l):
        t = l.strip()
        if t[0] != '[' and t[-1] != ']':
            print("case data: input a str 2dementionary list wrongly!", t)
            return
        t = t[1:-1]  # []

        ListStrs = []
        p1, p2 = 0, 0
        lock = True
        # print(t)
        while p2 < len(t):
            if t[p2] == '[' and lock:  # meet a [
                lock = False
            if t[p2] == ']' and not lock:  # meet a ], append a string of 1D list
                lock = True
                ListStrs.append(t[p1:p2 + 1])
                while p2 < len(t) and t[p2] != ',':  # go to next ','
                    # print(t[p2],end='-')
                    p2 += 1
                if p2 < len(t):
                    p1 = p2 + 1
                    p2 = p2 + 1
                    # print(p1,t[p1])
                else:
                    break
            else:
                p2 += 1

        # print(ListStrs)

        # print(t)

        rs = []
        # print(t)
        for elem in ListStrs:
            if elem != '':
                # print(elem)
                rs.append(self.getBinaryTree(elem))
        return rs

    def TreeListMapper(self, l):
        # used in map function when generate list from a line (Str2List)
        if l == 'null' or l == '':
            return None
        if True:
            # print("```",l)
            return int(l)
        else:
            return l
    def NumberMapper(self,l):
        # used in map function when generate list from a line (Str2List)|advanced
        if l == 'null' or l == '':
            return None
        if l.find('.')!=-1:
            return float(l)
        else:
            return int(l)
    def Str2List(self, l):
        t = l.strip()  # 去除回车符
        if t[0] != '[' and t[-1] != ']':
            print("case data: input a int list wrongly!", t)
            return
        t = t[1:-1]
        t = t.split(',')  # 分割元素
        if t[0] == '':
            t.pop()
        else:
            t = list(map(self.NumberMapper, t))  # str to int|float
        return t

    def getBinaryTree(self, l):
        tlist = self.Str2List(l)
        if not tlist:
            return None
        "使用队列进行处理"
        queue = []
        root = TreeNode(tlist[0])
        queue.append(root)
        index = 1
        flag = True  # true 插左节点，false插右
        while len(queue) and index < len(tlist):
            lastNode = queue[0]
            if flag:
                if isinstance(tlist[index], int):
                    temp = TreeNode(tlist[index])
                    lastNode.left = temp
                    queue.append(temp)
                else:
                    '''insert nothing'''
                flag = False
            else:
                if isinstance(tlist[index], int):
                    temp = TreeNode(tlist[index])
                    lastNode.right = temp
                    queue.append(temp)
                else:
                    '''insert nothing'''
                flag = True
                queue.pop(0)
            index += 1
        return root

    def verify2DIntsAns(self, a1: List[List[int]], a2: List[List[int]], eqtor=operator.eq) -> bool:
        # print(a1,a2)
        a1 = a1.copy()
        a2 = a2.copy()
        if len(a1) != len(a2):
            return False
        for elem in a1:
            Flag = False
            for elem2 in a2:
                if operator.eq(elem, elem2):
                    Flag = True
                    a2.remove(elem2)
                    break
            if not Flag:
                return Flag
        if len(a2):
            return False
        return True

    def verify2DStrsAns(self, a1: List[List[int]], a2: List[List[int]], eqtor=operator.eq) -> bool:
        return self.isListEqualNoOder(a1, a2, eqtor)

    def verifyListNodeAns(self, h1: ListNode, h2: ListNode) -> bool:
        p1 = h1
        p2 = h2
        while p1 and p2:
            if p1.val != p2.val:
                return False
            p1 = p1.next
            p2 = p2.next
        if p1 or p2:
            return False
        else:
            return True

    def verifyBinaryTreeNode(self, r1: TreeNode, r2: TreeNode):

        def recur(r1: TreeNode, r2: TreeNode):
            if r1.val != r2.val:

                return False
            if (r1.left and not r2.left) or (r2.left and not r1.left):

                return False
            if (r1.right and not r2.right) or (r2.right and not r1.right):
                #print(1222)
                return False
            rs1 = rs2 = True
            if r1.left:
                rs1 = recur(r1.left, r2.left)
            if r1.right:
                rs2 = recur(r1.right, r2.right)
            if not r1.left and not r2.left and not r1.right and not r2.right:
                #print(r1.val,r2.val)
                return r1.val == r2.val
            #print(rs1 and rs2)
            return rs1 and rs2

        if r1 and r2:
            return recur(r1, r2)
        if (r1 and not r2) or (r2 and not r1):
            return False
        return True

    def isListEqualNoOder(self, a1: List, a2: List, eqtor=operator.eq) -> bool:
        if type(a1) != type([]):
            return a1 == a2
        a1 = a1.copy()
        a2 = a2.copy()
        for elem in a1:
            Flag = False
            for elem2 in a2:
                if eqtor(elem, elem2):
                    Flag = True
                    a2.remove(elem2)
                    break
            if not Flag:
                return Flag
        if len(a2):
            return False
        return True

    def copyTreeNode(self, tr1: TreeNode, tr2: TreeNode):

        def inorder(n1: TreeNode, n2: TreeNode):
            if n1.left:
                temp = TreeNode(n1.left.val)
                n2.left = temp
                inorder(n1.left, n2.left)

            n2.val = n1.val
            if n1.right:
                temp = TreeNode(n1.right.val)
                n2.right = temp
                inorder(n1.right, n2.right)

        inorder(tr1, tr2)


class Printer:
    def print2DList(self, list1, size=3):
        for line in list1:
            for elem in line:
                print(repr(elem).rjust(size), end=' ')
            print()
        print()

    def printListNode(self, head: ListNode):
        p = head
        if not p.next:
            print(p.val, end='->Null')
            return
        # p=p.next
        while p:
            print(p.val, end=' -> ')
            p = p.next
        print('Null')

    def printBinrayTree(self, root: TreeNode):
        """
        指定一个最大宽度，是最下层每个数字均匀输出的长度
        双栈先序遍历树，每一层 的每个元素按照最大宽度均匀输出
        :param root:
        :return:
        """

        def getDepth(node: TreeNode) -> int:
            if not node:
                return 0
            left = right = 0

            left = getDepth(node.left)
            right = getDepth(node.right)
            return max(left, right) + 1

        p = root
        if not root:
            print("Nothing in tree.")
            return
        depth = getDepth(p)
        bottomWidth = 4
        width = pow(2, depth - 1) * bottomWidth
        stack1 = []
        stack2 = []
        nowDep = 0
        stack1.append(root)
        while stack1 or stack2 and nowDep < depth:
            if stack2:
                temp = stack1
                stack1 = stack2
                stack2 = temp
            # 指定宽度
            perWidth = width // pow(2, nowDep)
            for elem in stack1:
                # print this

                # insert sub node
                if elem:
                    form = "{:^" + str(perWidth) + "d}"
                    print(form.format(elem.val), end='')
                    stack2.append(elem.left)
                    stack2.append(elem.right)
                else:
                    form = "{:^" + str(perWidth) + "s}"
                    print(form.format("_"), end='')
                    stack2.append(None)
                    stack2.append(None)
            print()
            nowDep += 1
            stack1.clear()
