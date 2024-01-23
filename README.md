<h1 align="center">
	🍴 philosophers
</h1>

<p align="center">
	<b><i>I never thought philosophy would become so lethal</i></b><br>
</p>

<h3 align="center">
	<a href="#%EF%B8%8F-about">About</a>
	<span> · </span>
	<a href="#%EF%B8%8F-usage">Usage</a>
	<span> · </span>
	<a href="#-testing">Testing</a>
</h3>

---

<p align="center">
	<img width="250" alt="screenshot" src="https://github.com/mhernangilp/philo/assets/123759990/92442bb5-faf2-4f64-a200-67c8c5262ebb">
</p>

## 💡 About the project

> _In this project, you will learn the basic principles of threading a process.
You will learn how to create threads and discover mutex._


For more detailed information, look at the [**subject of this project**](https://github.com/mhernangilp/philo/blob/main/es.subject.philo.pdf).


## 🛠️ Usage

### Requirements

The function is written in C language and thus needs the **`gcc` compiler** and some standard **C libraries** to run.

### Instructions

**1. Compiling**

To compile, go to the project path and run:

```shell
$ make
```


## 📋 Testing

To execute the program, run:

```shell
$ ./philo <number_of_philosophers> <time_to_die time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

An example with 4 philosophers, 410 ms to die, 200 ms to eat and 200 ms to sleep:

```shell
$ ./philo 4 410 200 200
```

In this case no one dies, but if we put 310 ms to die instead:

```shell
$ ./philo 4 310 200 200
```

There will be a moment where one of them will die because the time elapsed since the last meal exceeded the time to die.
