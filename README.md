# Горбунова Софья ДВБ7-ЛА2 Лабораторная №4 Вариант №2
# Задание 1

## Задача 2

### Текст задачи

Реализовать класс Money с полями unsigned int rubles и short int
kopeks. Добавление произвольного количества копеек (unsigned int) к объекту типа Money. 
Результат должен быть типа Money

### Алгоритм решения

1. Создать класс с полями рублей и копеек. Допустимое значение копеек —
   от 0 до 99.
2. Реализовать конструктор без параметров, конструктор с количеством рублей
   и конструктор с рублями и копейками. Во всех случаях объект остается в
   корректном состоянии.
3. Перегрузить operator<< для вывода рублей и копеек с двумя цифрами после
   разделителя.
4. Реализовать AddKopeks: сложить сумму в копейках, нормализовать ее в рубли
   и копейки и вернуть новый объект. При выходе за диапазон рублей сообщить об
   ошибке переполнения.
5. Считывать ввод построчно и принимать только целые неотрицательные числа;
   копейки дополнительно проверять на диапазон 0–99.
6. Вывести меню выбора конструктора и операций. Для меню и
   числового ввода проверять, что строка содержит ровно одно число допустимого
   диапазона.
   
### Тестирование 

<img width="502" height="450" alt="image" src="https://github.com/user-attachments/assets/b7fd34eb-1911-44e4-8163-e612a604ca82" />
<img width="557" height="465" alt="image" src="https://github.com/user-attachments/assets/075b494c-ebdc-4578-8554-a0236949231d" />
<img width="522" height="488" alt="image" src="https://github.com/user-attachments/assets/e6afb249-8e1b-4b4f-8e3b-7afb669d7e30" />
<img width="572" height="487" alt="image" src="https://github.com/user-attachments/assets/7a87816a-b03c-4f3c-8ec7-551ec98d70fe" />
<img width="542" height="533" alt="image" src="https://github.com/user-attachments/assets/c8a60a2d-b83b-4f9e-9095-d0d713bfe82d" />
<img width="537" height="537" alt="image" src="https://github.com/user-attachments/assets/0fde3516-3ff5-4b7a-8d44-58524dc3f895" />
<img width="505" height="263" alt="image" src="https://github.com/user-attachments/assets/e7183097-0310-4a18-b92f-e129cd9e612d" />
<img width="572" height="360" alt="image" src="https://github.com/user-attachments/assets/3fb1ab69-4b2c-4b5b-bb9a-eea4a84e161c" />



# Задание 2

## Задача 2

### Текст задачи

Унарные операции:
++ добавление копейки к объекту типа Money
-- вычитание копейки из объекта типа Money
Операции приведения типа:
unsigned int (явная) – результатом является количество рублей (копейки
отбрасываются);
double (неявная) – результатом является копейки, переведенные в рубли,
целые рубли отбрасываются, результат <1.
Бинарные операции:
+ Money m, беззнаковое целое число (копейки). Результат должен быть
типа Money.
– Money m, беззнаковое целое число (копейки). Результат должен быть
типа Money.

### Алгоритм решения

1. Реализовать операции ++ и -- через сложение или вычитание одной копейки.
   Постфиксные операции сохраняют и возвращают прежнее значение.
2. Для unsigned int вернуть поле рублей, отбрасывая копейки. Для double
   разделить количество копеек на 100.
3. В бинарных операциях сначала получить общее количество копеек. При
   сложении нормализовать результат; при недостаточном остатке для вычитания
   сообщить об ошибке.
4. В main показать результаты всех операций на введенном пользователем
   объекте через меню.

### Тестирование 
<img width="493" height="511" alt="image" src="https://github.com/user-attachments/assets/1fb33085-cf4f-49d6-bd29-20b4131fbc2f" />
<img width="395" height="257" alt="image" src="https://github.com/user-attachments/assets/042c2c1d-6a82-4cbc-a306-2263b9645b07" />
<img width="392" height="187" alt="image" src="https://github.com/user-attachments/assets/f735cd58-0623-4b74-ae36-fba023ba1bab" />
<img width="425" height="207" alt="image" src="https://github.com/user-attachments/assets/55f40b95-e3fb-432d-bfc3-e4d44f2306c7" />
<img width="516" height="453" alt="image" src="https://github.com/user-attachments/assets/e9f0405d-8bf5-417f-9635-69f2ef25fa42" />
<img width="628" height="357" alt="image" src="https://github.com/user-attachments/assets/33708056-bde1-4861-8775-5af59b4db6a8" />
<img width="655" height="353" alt="image" src="https://github.com/user-attachments/assets/7370a169-51b3-4da5-81b5-0950d46ad6d3" />
<img width="706" height="360" alt="image" src="https://github.com/user-attachments/assets/9e1d0175-31c9-4dcd-9b6e-e8f6e9e392e9" />
<img width="623" height="282" alt="image" src="https://github.com/user-attachments/assets/c88c3881-1414-4039-a12b-2b8d25a717c6" />


   
