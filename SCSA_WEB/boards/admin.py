from django.contrib import admin
from .models import PutUserInfo, Petition, StaticData
# Register your models here.

admin.site.register(PutUserInfo)
admin.site.register(Petition)
admin.site.register(StaticData)
