#!/bin/sh
#
# testutils.sh - Misc utilities for testing the GNU recutils.
#
# Copyright (C) 2010 Jose E. Marchesi.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

# Create an input file.
# 
# $1 => Name of the file.
# $2 => Contents of the file.
test_declare_input_file ()
{
    # Check parameters.
    if test "$#" -ne "2"
    then
        echo "error: testutils: invalid parameters to declare_input_file"
        exit 1
    fi

    filename="$1.in"
    contents="$2"

    # Create the input file.
    echo -n "$contents" > $filename

    # Add the file to the global list of temp files.
    test_tmpfiles="$test_tmpfiles $filename"
}

# Initialize the testing environment.
#
# $1 => Name of the test suite.
test_init ()
{
    if test "$#" -ne "1"
    then
        echo "error: testutils: invalid parameters to test_init"
        exit 1
    fi

    test_suite=$1
    test_result="0"
    trap 'rm -fr $test_tmpfiles' EXIT 1 2 3 15

    echo "Running $test_suite test(s): "
}

# Delete temporary files and other cleanup.
#
# No parameters.
test_cleanup ()
{
    rm -fr $test_tmpfiles
    return $test_result
}

# Test a recutil.
#
# $1 => Test name.
# $2 => Utility to test.
# $3 => Parameters.
# $4 => Input file to use.
# $5 => Expected result.
test_tool ()
{
    # Check parameters.
    if test "$#" -ne "5"
    then
        echo "error: testutils: invalid parameters to test_tool"
        exit 1
    fi

    echo -n "  $1 "

    utility=$2
    parameters=$3
    input_file="$4.in"
    ok_file="$1.ok"
    output_file="$1.out"
    expected=$5

    test_tmpfiles="$test_tmpfiles $output_file $ok_file"

    # Run the tool.
    eval "cat $input_file | $utility $parameters > $output_file"
    res=$?
    if test "$res" -ne "0"
    then
        echo "error: testutils: test_tool: running $utility."
        return 1
    fi

    # Check for the result in output_file.
    echo -n "$expected" > $ok_file
    cmp $ok_file $output_file > /dev/null 2>&1
    res=$?
    if test "$res" -eq "0"
    then
        echo "ok"
    else
        echo -n "fail"
        echo " (see $1.diff)"
        diff $ok_file $output_file > $1.diff
    fi

    # Accumulate the error.
    test_result=`echo "$test_result + $res" | bc`
}

# End of testutils.sh