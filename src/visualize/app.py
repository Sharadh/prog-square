from flask import (
    Flask,
    send_file,
    send_from_directory
)
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
