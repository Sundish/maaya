# maaya

## What it does
Prints the current time in two posible ways, long round format:

```
$ maaya
$ 0.0.8.7.10

$ maaya -l
$ 0.0.8.7.10
```

The second one is according the Calendar round:

```
$ maaya -c 
$ 5 Ok 8 Pop
```

## Installation
Just run `make` and `make install` to copy the binary file to `/usr/bin`

#### NOTE for `make install` you'll need to be on a LINUX system

## Future Features

- To format any date to its long/calendar form
- Format from long/calendar to its Gregorian counterpart
- Add or substract long/calendar dates
- Print extra information such as: _year bearers_, _Lords of the night_, _Meaning of the days_ and more...
- Support for custom printing formats
