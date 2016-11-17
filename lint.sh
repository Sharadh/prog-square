#!/bin/bash

echo "Running pep8..."
pep8 src/ && echo "OK!"

echo "Running flake8..."
flake8 src/ && echo "OK!"
