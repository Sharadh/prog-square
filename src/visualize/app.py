import json
from datetime import datetime
from functools import wraps

from flask import (
    Flask,
    jsonify,
    make_response,
    send_file,
    send_from_directory
)

from generate.p2_convert import split_meta_source

app = Flask(__name__, static_folder='package/static')


def no_cache(view):
    @wraps(view)
    def f(*args, **kwargs):
        response = make_response(view(*args, **kwargs))
        response.headers['Last-Modified'] = datetime.now()
        response.headers['Cache-Control'] = ' '.join([
            'no-store', 'no-cache', 'must-revalidate',
            'post-check=0', 'pre-check=0', 'max-age=0'
            ])
        response.headers['Pragma'] = 'no-cache'
        response.headers['Expires'] = '-1'
        return response

    return f


@app.route('/home')
def index():
    return app.send_static_file('index.html')


@app.route('/static/<path:path>')
def resources(path):
    return send_from_directory('package/static', path)


@app.route('/graph/default')
@no_cache
def default():
    return send_file('./package/graph.json')


@app.route('/graph/default/snippet/<int:program_id>')
@no_cache
def snippet(program_id):
    with open('./package/manifest.json', 'r') as manifest_file:
        manifest = json.load(manifest_file)
    program_meta = manifest[str(program_id)]
    program_filepath = program_meta['filepath']
    app.logger.info("snippet({}) --> {}".format(program_id, program_filepath))

    with open(program_filepath, 'r') as input_file:
        data = input_file.read()

    meta, source = split_meta_source(data)
    response_data = {
        'meta': meta,
        'data': source.strip()
    }
    return jsonify(response_data)
