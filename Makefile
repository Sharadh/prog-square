VENV_DIR=./venv
VENV_ACTIVATE_SCRIPT=$(VENV_DIR)/bin/activate
PIP_VERSION=9.0.1
SOURCE?='data/practice-python'
DEST?=''
MANIFEST?=''
DEBUG?=0
FLASK_CONFIG=FLASK_APP=app.py FLASK_DEBUG=$(DEBUG)

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
	@. $(VENV_ACTIVATE_SCRIPT); . './lint.sh'

clean:
	@find src/ -iname "*.pyc" -exec rm {} \;

console: install
	@. $(VENV_ACTIVATE_SCRIPT); cd src; ipython

test: install
	@nosetests tests/

.PHONY: install reinstall lint clean console test

run: install
	@. $(VENV_ACTIVATE_SCRIPT); cd src; python cli.py order $(SOURCE) -o $(DEST) -m $(MANIFEST)

serve: install
	@. $(VENV_ACTIVATE_SCRIPT); cd src/visualize;\
	 $(FLASK_CONFIG) python -m flask run

visualize: install
	@. $(VENV_ACTIVATE_SCRIPT); cd src;\
	 python cli.py order $(SOURCE) -o 'src/visualize/package/graph.json' -m 'src/visualize/package/manifest.json'
	@. $(VENV_ACTIVATE_SCRIPT); cd src/visualize;\
	 $(FLASK_CONFIG) python -m flask run

so-recent: install
	@rm -rf data/so_temp; mkdir data/so_temp
	@. $(VENV_ACTIVATE_SCRIPT); cd src;\
	 python cli.py pull_so_recent 'data/so_temp' -c 100


.PHONY: run serve visualize
