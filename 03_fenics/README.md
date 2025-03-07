# Лабораторная по работе с FEniCS

Для изучения был выбран стандартный пример из документации [Poisson equation](https://fenics.readthedocs.io/projects/dolfin/en/2017.2.0/demos/poisson/python/demo_poisson.py.html).

## Постановка задачи
Моделировалось уравнение Пуассона для электростатики в условии отсутствия объёмного заряда:

```math
\Delta u =0
```

В качестве геометрии была взята одна из установок из лабораторной работы круса общей физики "Моделирование плоских электростатических полей". 
Описание можно найти [тут](https://old.mipt.ru/education/chair/physics/S_III/lab_el/34pp-%D0%9C%D0%BE%D0%B4%D0%B5%D0%BB%D0%B8%D1%80.%20%D1%8D%D0%BB.%20%D0%BF%D0%BE%D0%BB%D0%B5%D0%B9_2013-IX.pdf).

| Установка  | Сетка |
| ------------- | ------------- |
|  <img src="https://github.com/Vioma-tech/miniscience-4th-term/blob/main/03_fenics/img/exp-setup.jpg" width=900> | ![image](https://github.com/user-attachments/assets/d85d2bf6-2de2-40b2-9611-ada9bd770739)  |

Граничные условия на свободных торцах задавались условием фон Неймана (см. [документацию](https://fenics.readthedocs.io/projects/dolfin/en/2017.2.0/demos/poisson/python/demo_poisson.py.html)).
Причём функция g приравнивалась нулю, так как на свободном конце напряженность электричсекого поля не имеет компоненты, перпендикулятной данному краю:

```math
(\nabla u,\:n)=(-E,\:n)=0\;\text{  на  }\;\Gamma_N=\text{свободные торцы}
```

На оставшихся угловых границ задавалось условие Дирихле: на одном из углов потенциал был нулевой потенциал u, а на другом - 18:

```math
u_1=0\;\text{  на  }\;\Gamma_{D_1}=\text{верхний угол}
```
```math
\;u_2=18\;\text{  на  }\;\Gamma_{D_2}=\text{нижний угол}
```

## Результат

![el-pot-field-model](https://github.com/Vioma-tech/miniscience-4th-term/blob/main/03_fenics/img/u-field-model.png)

## Сравнение с экспериментом

| Эксперимент  | Моделирование |
| ------------- | ------------- |
| <img src="https://github.com/Vioma-tech/miniscience-4th-term/blob/main/03_fenics/img/exp_field.png" width=1400> | ![u-field-model-crop](https://github.com/user-attachments/assets/b1303ef3-211a-48d5-8b11-e6c96c6e2728) |

