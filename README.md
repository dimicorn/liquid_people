# Жидкие люди
## Условие задачи
Поведение толпы можно описать моделями гидро- и газодинамики, например сёрклпит описывали как вихрь в жидкости ([статья](https://sethna.lassp.cornell.edu/pubPDF/MoshPits.pdf)). Предложите эксперимент, в котором толпа людей будет вести себя подобно текущей жидкости или газу. Как свойства эквивалентной среды (например, вязкость) зависят от важных параметров? Может ли в вашей модели образоваться затор возле выхода из комнаты?
## Решение
### Установка GSL
 ```
 wget https://gnu.mirror.constant.com/gsl/gsl-latest.tar.gz
 tar xzvf gsl-latest.tar.gz
 sudo ./configure && make && make install
 ```
 If the above gives a "permission denied" error, instead try
 ```
sudo make clean
sudo chown -R $USER .
./configure && make
make install
```