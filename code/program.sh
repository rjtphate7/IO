#!/bin/bash


avrdude -c usbasp -p m8 -U flash:w:io.hex
