import sys

def parse_stats(perf, gpu_usage):

    perfs = []
    with open(perf) as f:

        while True:
            l = f.readline()
            if l:
                n = l.split()[1].strip()
            else:
                n = None
            #print(n)
            if l and n != 'FPS' and n != '0.00':
                perfs.append(float(n))
            if not l:
                break


    gpu_usages = []
    with open(gpu_usage) as f:
        while True:
            l = f.readline()
            if l:
                usage = l.split('GR3D_FREQ')[-1].strip().split()[0].replace('%','')
                if int(usage) > 0:
                    gpu_usages.append(int(usage))
            else:
                break


    import numpy as np

    #print(np.sort(perfs))
    worst_perf = np.sort(perfs)[0]



    tenth = len(gpu_usages) // 10
    if tenth == 0:
        tenth = 1


    avg_gpu_usage = np.average(np.sort(gpu_usages)[-tenth:])

    #print(worst_perf, avg_gpu_usage)
    return worst_perf, avg_gpu_usage