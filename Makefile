VENV_DIR=./venv
VENV_ACTIVATE_SCRIPT=$(VENV_DIR)/bin/activate
PIP_VERSION=9.0.1
SOURCE?='data/practice-python'
DEST?=''

default: run

venv:
ifeq ("","$(wildcard "$(VENV_ACTIVATE_SCRIPT)")")
	@virtualenv $(VENV_DIR)
	@\
		. "$(VENV_ACTIVATE_SCRIPT)"; \
		pip install pip==$(PIP_VERSION); \
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

.PHONY: install reinstall lint clean console test

run: install
	@. $(VENV_ACTIVATE_SCRIPT); cd src; python cli.py order $(SOURCE) -o $(DEST)

visualize: install
	@. $(VENV_ACTIVATE_SCRIPT); cd src;\
	 python cli.py order $(SOURCE) -o 'src/visualize/package/graph.json'
	@. $(VENV_ACTIVATE_SCRIPT); cd src/visualize;\
	 python main.py

.PHONY: run visualize
