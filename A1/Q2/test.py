import os

os.system("rm fail.txt")
os.system("make clean")
os.system("make throwcatch")
os.system("make longjmp")

g = open("fail.txt", "a");
for i in xrange(20):
    for j in xrange(20):
        for k in xrange(20):
            os.system("./throwcatch %s %s %s > throwcatch.txt" % (i, j, k))
            os.system("./longjmp %s %s %s > longjmp.txt" % (i, j, k))
            os.system("diff throwcatch.txt longjmp.txt > diff.txt")
            f = open("diff.txt").readlines()
            fail = False
            for line in f:
                line = line.strip()
                if line and line.startswith('>') or (line.startswith('<') and '~T' not in line):
                    fail = True
            if fail:
                msg = "%s, %s, %s Failed\n" % (i, j, k)
                g.write(msg)
