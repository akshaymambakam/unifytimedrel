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

A more detailed user guide for the tool can be found in:
```
eitre_guide.txt
```

## Using the MPTRE tool
The MPTRE tool implements efficient PTPM and Parametric Identification for Parametric Timed Regular Expressions that allow magnitude parameters but no timing parameters that deal with real-valued signals. You can run MPTRE on an example we gave using the following command:
```
./mptre paramecg.ptre debugTest.csv 3 pos_ecg.txt neg_ecg.txt
```
In the above command: 'paramecg.ptre' contains the PTRE, 'debugTest.csv' the signal, the third argument is the number of parameters, and labels for positive and negative examples are provided in 'pos_ecg.txt' and 'neg_ecg.txt' respectively.

A more detailed user guide for the tool can be found in:
```
mptre_guide.txt
```

## Using the PEBTRE tool
The PEBTRE tool implements full semantics PTPM for Parametric Event-Based Timed Regular Expressions. By full semantics we mean that we do not require the start of a match to be exactly when events happen. You can run PEBTRE on an example we gave using the following command:
```
./pebtre ecgtrigeminy.ptre ecg106_seq.txt 4
```
In the above command: 'ecgtrigeminy.ptre' contains the PTRE, 'ecg106_seq.txt' the timed word, and the third argument is the number of parameters.

## Authors and acknowledgment
This tool builds on the work that was done at the VERIMAG laboratory located in the Grenoble city of France. This work is built on top of the theory of Timed Pattern Matching (TPM) developed by [Dogan Ulus](https://www.cmpe.boun.edu.tr/tr/people/dogan.ulus). Check out his [github page](https://github.com/doganulus). Timed Pattern Matching has been implemented in [montre](https://github.com/doganulus/montre) and [timedrel](https://github.com/doganulus/timedrel).

## License
For open source projects, say how it is licensed.