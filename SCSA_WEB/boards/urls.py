from django.urls import path
from . import views

app_name = 'boards'

urlpatterns = [
    path('', views.index, name='index'),
    path('index/', views.start, name='start'),
    path('tologin/', views.tologin, name='tologin'),
    path('gotosignup/', views.gotosignup, name = 'gotosignup'),
    path('signup/', views.signup, name = 'signup'),
    path('texttodb/', views.texttodb, name = 'texttodb'),
    path('returntoregister/', views.returntoregister, name ='returntoregister'),
    path('register/', views.register, name='register'),
]
