import json

from flask import (
    Flask,
    jsonify,
    send_file,
    send_from_directory
)

from p2_convert import split_meta_source

app = Flask(__name__, static_folder='package/static')


@app.route('/home')
def index():
    return app.send_static_file('index.html')


@app.route('/static/<path:path>')
def resources(path):
    return send_from_directory('package/static', path)


@app.route('/graph/default')
def default():
    return send_file('./package/graph.json')


@app.route('/graph/default/snippet/<int:program_id>')
def snippet(program_id):
    with open('./package/manifest.json', 'r') as manifest_file:
        manifest = json.load(manifest_file)
    program_filepath = manifest[str(program_id)]
    app.logger.info("snippet({}) --> {}".format(program_id, program_filepath))

    with open(program_filepath, 'r') as input_file:
        data = input_file.read()

    meta, source = split_meta_source(data)
    response_data = {
        'meta': meta,
        'data': source.strip()
    }
    return jsonify(response_data)
