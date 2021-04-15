# maaya

## What it does
### Printing Dates
Currently there's only two ways to print the date, long round format:

```
$ maaya
$ 0.0.8.7.10

$ maaya -l
$ 0.0.8.7.10
```

The second one is according to the Calendar round:

```
$ maaya -c 
$ 5 Ok 8 Pop
```
### Modifying Dates
By using the plus sign you can add dates together:

```
$ maaya + 0.0.1.2.1 0.9.1.0.0
$ 0.9.2.2.1
```

## Installation
Just run `make` and `make install` to copy the binary file to `/usr/bin`

#### NOTE for `make install` you'll need to have `/usr/bin` path.

## Future Features

- To format any date to its long/calendar form
- Format from long/calendar to its Gregorian counterpart
- add and substract calendar round dates
- substract long count dates
- Print extra information such as: _year bearers_, _Lords of the night_, _Meaning of the days_ and more...
- Support for custom printing formats
