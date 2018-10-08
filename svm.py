from os import listdir
from sklearn.model_selection import train_test_split
import cv2
import numpy as np
from sklearn import svm
from sklearn.metrics import accuracy_score

def loadImages(path):

    imagesList = listdir(path)
    loadedImages = []
    for image in imagesList:
        img = cv2.imread(path + image,0)
        loadedImages.append(img)

    return loadedImages

path = "flowers/daisy/"
path2 = "flowers/dandelion/"

daisy = loadImages(path)
dandelion = loadImages(path2)
for img in daisy:
    img = np.asarray(img)
for img in dandelion:
    img = np.asarray(img)    
daisy = np.asarray(daisy)
dandelion = np.asarray(dandelion)
daisy_labels = np.ones((daisy.shape[0],1))
dandelion_labels = np.zeros((dandelion.shape[0],1))
X = np.concatenate((daisy,dandelion),axis=0)
y = np.concatenate((daisy_labels,dandelion_labels),axis=0)


X_train, X_test, y_train, y_test = train_test_split( X, y, test_size=0.4, random_state=42)
model = svm.SVC(gamma=0.01,C=100)
model.fit(X_train,y_train)
y_pred = model.predict(X_test)

print(str(accuracy_score(y_test,y_pred)))
