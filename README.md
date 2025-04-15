# Homework.
Егор Шастин Олегович, gruppa b81-mm
Contact: st129457@student.spbu.ru,egor.shast0.0@gmail.com

# Vectorized Gaussian Method

## Overview

This program reads a matrix from a CSV file, performs the Gauss method on it to transform it to a triangular shape, and saves the result to a new CSV file. If the source file is not found, the program automatically creates a random matrix.

## Table of Contents
- [Installation and Build](#installation-and-build)
- [Tests](#tests)

## Installation and Build

### Building the Project

```sh
make
```

### Running the Programm
To start the programm, run the compiled executable:

```sh
./bin/Start # Run general programm
```

## Tests

#### Continuous Integration (CI)
This project uses GitHub Actions for automated builds and testing. All tests are run in the CI pipeline on every commit.

#### Running Tests Locally
To run tests locally, you can use the following commands:

```sh
make test        # Runs unit tests for all programm
```

