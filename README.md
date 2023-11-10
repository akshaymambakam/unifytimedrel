# Unifying the algorithms for timed relations and parametric timed relations
This repository aims to provide algorithms for parametric timed relations based on the the timed relations code base (for Timed Pattern Matching) from [timedrel](https://github.com/doganulus/timedrel). The code for parametric timed relations can be used to create tools for Parametric Timed Pattern Matching (PTPM) and Parametric Identification fors Parametric Timed Regular Expressions (PTRE).


## Installation
We give installation instructions for Ubuntu.
1. Install Parma Polyhedra Library (PPL).
```
sudo apt install ppl-dev
```
2. Install C++ compiler.
```
sudo apt install g++
```
3. Install parsing and lexing tools.
```
sudo apt install bison
sudo apt install flex
```
4. Install the GNU Multiple Precision (GMP) Arithmetic Library.
```
sudo apt install libgmp-dev
```
5. Install make
```
sudo apt install make
```
6. Once inside the folder install and generate the binaries for the tools by running make.
```
make
```

## Using the EITRE tool
The EITRE tool implements efficient PTPM and Parametric Identification for Parametric Timed Regular Expressions (event-based) that deal with timed words. You can run EITRE on an example we gave using the following command:
```
./eitre eloop.ptre testBlowup.csv 3 pos_labels.txt neg_labels.txt
```
In the above command: 'eloop.ptre' contains the PTRE, 'testBlowup.csv' the timed word, the third argument is the number of parameters, and labels for positive and negative examples are provided in 'pos_labels.txt' and 'neg_labels.txt' respectively.

## Authors and acknowledgment
This tool builds on the work that was done at the VERIMAG laboratory located in the Grenoble city of France. This work is built on top of the theory of Timed Pattern Matching (TPM) developed by [Dogan Ulus](https://www.cmpe.boun.edu.tr/tr/people/dogan.ulus). Check out his [github page](https://github.com/doganulus). Timed Pattern Matching has been implemented in [montre](https://github.com/doganulus/montre) and [timedrel](https://github.com/doganulus/timedrel).

## License
For open source projects, say how it is licensed.