# Benchmark
CPU benchmark based on md5, computing avg hashes / s <br>
<br>
## Usage
### Benchmark
`./benchmark.out -d` - run with default parameters - 4 processes and word "koko" <br>
`./benchmark.out` - interactive read parameters <br>
`./benchmark.out -p 16 -w ok` - run brute-force hashes computing on 16 processes till break work "ok" <br>

### Brute force hash breaking
`./benchmark.out -h98dc261b971350351fbb227ef6de1afb -l4 -p8` - try to break hash of word "kotA" using 8 processes
