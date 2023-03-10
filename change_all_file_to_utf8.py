import os
import shutil


def Step1():
    FAILED = []
    for root, dirs, files in os.walk(ROOT):
        for i in dirs:
            if i.startswith('.vs'): shutil.rmtree(os.path.join(root, i))
            if not os.listdir(os.path.join(root, i)): shutil.rmtree(os.path.join(root, i))
        for i in files:
            if not i.endswith(('.cpp', '.h', '.txt')):
                os.remove(os.path.join(root, i))
            elif i.endswith(('.cpp', '.h')):
                try:
                    content = open(os.path.join(root, i), 'r', encoding='gbk').read()
                    open(os.path.join(root, i), 'w', encoding='UTF-8').write(content)
                except:
                    try:
                        content = open(os.path.join(root, i), 'r', encoding='utf-8').read()
                        open(os.path.join(root, i), 'w', encoding='UTF-8').write(content)
                    except:
                        print(f'{os.path.join(root, i)}修改失败')
                        FAILED.append(os.path.join(root, i))
    open('FAILED.txt', 'w', encoding='utf-8').write('\n'.join(FAILED))


def Step2():
    FAILED_old = open('FAILED.txt', 'r', encoding='utf-8').readlines()
    FAILED = []
    for root, _, files in os.walk(ROOT):
        for i in files:
            if os.path.join(root, i) in FAILED_old:
                try:
                    content = open(os.path.join(root, i), 'r', encoding='utf-8').read()
                    open(os.path.join(root, i), 'w', encoding='UTF-8').write(content)
                except:
                    print(f'{os.path.join(root, i)}修改失败')
                    FAILED.append(os.path.join(root, i))
    open('FAILED.txt', 'w', encoding='utf-8').write('\n'.join(FAILED))


if __name__ == '__main__':
    ROOT = input('1. 只保留.cpp、.h、.txt文件\n'
                 '2. 将编码格式统一为UTF-8\n'
                 '   输入要处理的根目录：')
    if os.path.exists('FAILED.txt') and open('FAILED.txt', 'r', encoding='utf-8').read():
        Step2()
    else:
        Step1()
