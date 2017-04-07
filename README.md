# MPI examples for ESIIAB's students
> Some MPI examples written in C. WORK IN PROGRESS

<!--One to two paragraph statement about your product and what it does.-->

![esiiab](https://www.esiiab.uclm.es/imgweb/portada/logo_esii.png)

## Installation

Debian/Ubuntu:

```sh
sudo apt-get install openmpi-bin openmpi-common openssh-client openssh-server libopenmpi1.3 libopenmpi-dbg libopenmpi-dev
```

Other distros:
see https://www.open-mpi.org/software/ompi/v2.1/

<!--Windows:
```sh
edit autoexec.bat
```
-->

## Usage example
```sh
bash mpi_exec.sh hello.c 4
```

<!--## Development setup

Describe how to install all development dependencies and how to run an automated test-suite of some kind. Potentially do this for multiple platforms.

```sh
make install
npm test
```
-->

## MPD daemon for running MPI programmes locally
``` #Create mpd .conf file
$ cd $HOME
$ touch .mpd.conf
$ chmod 600 .mpd.conf

#Add your own password (what you decide)
$ MPD_SECRETWORD=passwd >> .mpd.conf

#Launch the daemon in background
$ Mpd & 
```

## Contributing

1. Fork it!
2. Create your feature branch: `git checkout -b my-new-feature`
3. Commit your changes: `git commit -am 'Add some feature'`
4. Push to the branch: `git push origin my-new-feature`
5. Submit a pull request :D

## Release History

* 0.1.0
    * The first proper release
* 0.0.1
    * Work in progress

## Meta

AirQ – airq@protonmail.com  

Distributed under the MIT license. See ``LICENSE`` for more information.

[https://gitlab.com/airq](https://gitlab.com/airq)
[https://github.com/airqinc](https://github.com/airqinc)
