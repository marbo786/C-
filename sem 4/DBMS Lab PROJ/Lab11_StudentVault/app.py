import os
import psycopg2
from flask import Flask, render_template, request, redirect, url_for
from werkzeug.utils import secure_filename

app = Flask(__name__)
app.config['UPLOAD_FOLDER'] = 'static/uploads'
app.config['MAX_CONTENT_LENGTH'] = 16 * 1024 * 1024  

ADMIN_PASSWORD = "pgadmin4"

os.makedirs(app.config['UPLOAD_FOLDER'], exist_ok=True)

def get_db_connection():
    conn = psycopg2.connect(
        host="localhost",
        database="student_vault",
        user="postgres",
        password="marbo786"
    )
    return conn

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/add', methods=['GET', 'POST'])
def add_profile():
    if request.method == 'POST':
        name = request.form['name']
        major = request.form['major']
        age = request.form['age']
        
        file = request.files.get('profile_image')
        filename = None
        if file and file.filename != '':
            filename = secure_filename(file.filename)
            file.save(os.path.join(app.config['UPLOAD_FOLDER'], filename))

        conn = get_db_connection()
        cur = conn.cursor()
        cur.execute(
            'INSERT INTO profiles (name, major, age, image_filename) VALUES (%s, %s, %s, %s)',
            (name, major, age, filename)
        )
        conn.commit()
        cur.close()
        conn.close()
        
        return redirect(url_for('students'))
        
    return render_template('add_profile.html')

@app.route('/students')
def students():
    conn = get_db_connection()
    cur = conn.cursor()
    cur.execute('SELECT id, name, major, image_filename FROM profiles')
    profiles = cur.fetchall()
    cur.close()
    conn.close()
    return render_template('students.html', profiles=profiles)

@app.route('/admin', methods=['GET', 'POST'])
def admin():
    if request.method == 'POST':
        password = request.form['password']
        if password == ADMIN_PASSWORD:
            conn = get_db_connection()
            cur = conn.cursor()
            cur.execute('SELECT id, name, major, age, image_filename, created_at FROM profiles')
            profiles = cur.fetchall()
            cur.close()
            conn.close()
            return render_template('admin.html', profiles=profiles)
        else:
            return "Wrong Password"
            
    return render_template('admin_login.html')

if __name__ == '__main__':
    app.run(debug=True)
