from flask import Flask,request,jsonify,make_response
from flask_cors import CORS
from models.calculator import handle,config

app = Flask(__name__,static_url_path="")
CORS(app, supports_credentials=True)


@app.route('/')
def index():
    return app.send_static_file('index.html')

@app.route('/cal',methods=['POST'])
def cal():
    data=request.get_json()
    status,data,ways=handle(data)
    response={'status':status,'cost':data,}
    if ways is not None:response['ways']=ways
    return response

if __name__ == '__main__':
    print(config.getint('LuxuryFirstClass', 'carry_num'))
    app.run()
