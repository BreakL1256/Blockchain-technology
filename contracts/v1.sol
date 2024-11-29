// SPDX-License-Identifier: GPL-3.0

pragma solidity >=0.8.2 <0.9.0;

contract v1{
    
    struct Project {
        string name; 
        uint256 fundingGoal; 
        uint256 totalFunds; 
        uint256 deadline;
        address manager; 
        bool propertyPurchased; 
        mapping(address => uint256) contributions; 
        address[] investors; 
    }

    function createProject(string memory name, uint256 fundingGoal, uint256 durationInDays) external {
     
    }

    function investInProject(uint256 projectId) external payable {

    }

    function purchaseProperty(uint256 projectId) external {
    
    }

    function issueRefund(uint256 projectId) external {
    
    }

    
}