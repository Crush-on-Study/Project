from django.shortcuts import render, get_object_or_404 , redirect
from .models import PutUserInfo, Petition, StaticData
from django.shortcuts import get_object_or_404
from django.contrib.auth import authenticate, login , logout # 아이디, 비밀번호 일치 여부
from django.contrib import messages


def index(request):
    return render(request, 'boards/index.html')

def start(request):
    return render(request, 'boards/signin.html')

def tologin(request):
    inputusername = request.POST.get('username')
    inputpassword = request.POST.get('password')
    namecheck = PutUserInfo.objects.filter(username=inputusername, password=inputpassword)
    # user = authenticate(request, username=inputusername, password=inputpassword)
    if namecheck:
        # login(request, user)
        # request.session['username'] = inputusername
        return render(request,'boards/register.html')
    else:
        messages.error(request, '로그인에 실패하였습니다.')
        return render(request, 'boards/signin.html', {'login_failed': True})

def gotosignup(request):
    return render(request, 'boards/signup.html')

def signup(request): # 회원 가입
    username = request.POST.get('username')
    password = request.POST.get('password')
    email = request.POST.get('email')
    
    if username and password and email:
        info = PutUserInfo(username=username, password=password, email=email)
        info.save()
        return render(request, 'boards/register.html')
    
    else:
        return render(request, 'boards/signup.html')

def texttodb(request): # 청원 내용 작성
    category = request.POST.get('category')
    title = request.POST.get('title')
    content = request.POST.get('content')

    if category and title and content:
        info = Petition(category=category, title = title, content=content)
        info.save()

        ouputcontent = StaticData.objects.get(s_categorynum=category)
        # result = predict_result(content)
        result = {'name':"Transformer_KOREAN", 'score':50}
        context = {'result':result, 'ouput':ouputcontent}
        return render(request, 'boards/output.html', context)
    else:
        messages.error(request,'내용을 입력하세요.')
        return render(request, 'boards/register.html' , {'write_failed': True})
    
def returntoregister(request):
    return render(request, 'boards/register.html')

def register(request):
    return render(request, 'register.html')

def dashboard(request):
    username = request.session.get('username')
    if username:
        return render(request, 'boards/dashboard.html', {'username': username})
    else:
        return redirect('boards:start')

def logout_view(request):
    logout(request)
    return redirect('boards:start')
