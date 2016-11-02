VENV_DIR=./venv
VENV_ACTIVATE_SCRIPT=$(VENV_DIR)/bin/activate
SOURCE?='data/practice-python'
DEST?=''

default: run

venv:
ifeq ("","$(wildcard "$(VENV_ACTIVATE_SCRIPT)")")
	@virtualenv $(VENV_DIR)
	@\
		. "$(VENV_ACTIVATE_SCRIPT)"; \
		pip install pip==8.1.1; \
		pip install pip-tools
endif

requirements.txt: venv requirements.in
	@. $(VENV_ACTIVATE_SCRIPT); pip-compile

deps: requirements.txt
	@echo "Dependencies compiled and up to date"

install: venv requirements.txt
	@echo "Synching dependencies..."
	@. $(VENV_ACTIVATE_SCRIPT); pip-sync

reinstall:
	@rm -rf $(VENV_DIR)
	@make install

lint: install 
	@echo "Running pep8..."; . $(VENV_ACTIVATE_SCRIPT); pep8 src/ && echo "OK!"
	@echo "Running flake8..."; . $(VENV_ACTIVATE_SCRIPT); flake8 src/ && echo "OK!"

clean:
	@find src/ -iname "*.pyc" -exec rm {} \;

console: install
	@cd src; ipython

test: install
	@nosetests tests/

run: venv install
	@. $(VENV_ACTIVATE_SCRIPT); cd src; python cli.py order $(SOURCE) -o $(DEST)

.PHONY: default deps install reinstall lint clean console test run