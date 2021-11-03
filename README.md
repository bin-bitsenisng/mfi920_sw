afi910_sw 
========
How to Build
-------------
<pre>
<code>
./build.sh

</code>
</pre>
How to execute program
-------------
<pre>
<code>
# 아래 명령어는 전원 입력 후, 한번만 실행해주면 됩니다.
./afi910_example_startup.sh

# 실행
./execute_afi910_sw.sh [OPTION]
[OPTION]
    -h    help.
    -c    AI confidence threshold (0.0 ~ 1.0. Default is 0.5)
    -n    AI nms threshold (0.0 ~ 1.0. Default is 0.4)
    -r    camera resolution (4K, QHD, FHD, 720P, VGA. Default is VGA)

example) ./execute_afi910_sw.sh -c 0.4 -n 0.3 -r FHD

참고) High resolution 일수록 latency가 더 있음. 추후 개선 예정.
</code>
</pre>