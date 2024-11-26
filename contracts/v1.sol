// SPDX-License-Identifier: GPL-3.0

pragma solidity >=0.8.2 <0.9.0;

contract v1{
    uint age;

    function setAge(uint x) public{
        age = x;
    }

    function getAge() public view returns (uint){
        return age;
    }
}