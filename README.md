# Loop-Lenguage

## :stop_sign: Attention!

This language is still under development!
I introduce everyone to the LOOP programming language. This language was created for study purposes only, but you are free to do what you want... 
For now it does not support recursion, much less object orientation and there are no arithmetic operations. But as I said earlier, it is still in development.
If you were curious about the name, I gave it that name because I got stuck in loops hahaha.

- Obs: can only be used in a linux environment!

## Use with docker
Up and Exec container
```
$ docker-compose up -d --build
$ docker exec -it app bash
```

## Run with docker
Run
```
$ loop
```

## Installation
Install
```
$ sudo make install
```

## Clean
Clean
```
$ sudo make clean
```

## Build
Clean and Install
```
$ sudo make build
```


## Grammar
```C
/*
 * Declaring and using variables
 */

def name = "raissadev";

print(name);

/*
 * Declaring and using functions
 */

function example(a, b)
{
    print(a);
    print(b);
};

example("hello", "world");
```

## Test file
```
$ ./loop.out <filepath>
```


## Author
Raissa Daros - raissa.fullstack@gmail.com - https://github.com/Raissadev/

## License
This component is licensed under the MIT License.

