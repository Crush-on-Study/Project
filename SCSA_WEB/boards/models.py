from django.db import models

class PutUserInfo(models.Model):
    username = models.CharField(max_length=50)
    password = models.CharField(max_length=50)
    email = models.EmailField(max_length=254)

class Petition(models.Model):
    category = models.CharField(max_length=50)
    title = models.CharField(max_length=100)
    content = models.TextField()

class StaticData(models.Model):
    s_categorynum = models.CharField(max_length=50)
    s_categoryname = models.CharField(max_length=50)
    s_title = models.TextField()
    s_content = models.TextField()
    s_like = models.IntegerField()
    s_mean = models.IntegerField()
