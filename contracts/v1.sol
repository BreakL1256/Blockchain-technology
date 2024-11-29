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

    mapping(uint256 => Project) public projects;
    uint256 public projectCount;

    function createProject(string memory name, uint256 fundingGoal, uint256 durationInDays) external {
        uint256 projectId = projectCount; 
        projectCount++; 

        Project storage newProject = projects[projectId];
        newProject.name = name;
        newProject.fundingGoal = fundingGoal;
        newProject.totalFunds = 0;
        newProject.deadline = block.timestamp + (durationInDays * 1 days);
        newProject.manager = msg.sender;
        newProject.propertyPurchased = false;
    }

    function investInProject(uint256 projectId) external payable {

    }

    function purchaseProperty(uint256 projectId) external {
    
    }

    function issueRefund(uint256 projectId) external {
    
    }


}