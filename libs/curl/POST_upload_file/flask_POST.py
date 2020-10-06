"""
curl -X POST -H "Content-Type: application/json" -d {"name":"dhan"} http://localhost:8288/register
"""
from flask import Flask, request

app = Flask(__name__)

@app.route('/')
def hello_world():
    return 'hello world'

@app.route('/register', methods=['POST'])
def register():
    print("=== HEADERS ===:\n", request.headers)
    print("\n=== FORM ===:\n", request.form)
    print("\n=== FULL_PATH ===:\n", request.full_path)
    print("\n=== BODY ===:\n", request.get_data())
    """
    #do something else
    #
    #
    """
    return 'Done\n'

if __name__ == '__main__':
    app.run(port=8288,debug=True)

