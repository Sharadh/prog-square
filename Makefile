VENV_DIR=./venv
VENV_ACTIVATE_SCRIPT=$(VENV_DIR)/bin/activate

default: run

venv:
ifeq ("","$(wildcard "$(VENV_ACTIVATE_SCRIPT)")")
	@virtualenv $(VENV_DIR)
	@\
		source "$(VENV_ACTIVATE_SCRIPT)"; \
		pip install pip==8.1.1; \
		pip install pip-tools
endif

requirements.txt: venv requirements.in
	@source $(VENV_ACTIVATE_SCRIPT); pip-compile

deps: requirements.txt
	@echo "Dependencies compiled and up to date"

install: venv requirements.txt
	@echo "Synching dependencies..."
	@source $(VENV_ACTIVATE_SCRIPT); pip-sync

reinstall:
	@rm -rf $(VENV_DIR)
	@make install

lint: install 
	@echo "Running pep8..."; source $(VENV_ACTIVATE_SCRIPT); pep8 src/ && echo "OK!"
	@echo "Running flake8..."; source $(VENV_ACTIVATE_SCRIPT); flake8 src/ && echo "OK!"

clean:
	@find src/ -iname "*.pyc" -exec rm {} \;

console: install
	@cd src; ipython

test: install
	@nosetests tests/

run: venv install
	@source $(VENV_ACTIVATE_SCRIPT); cd src; python cli.py order '../data/hello'

.PHONY: default deps install reinstall lint clean console test run