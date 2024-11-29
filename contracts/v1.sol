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

    event ProjectCreated(uint256 projectId, string name, uint256 fundingGoal, uint256 deadline, address manager);
    event InvestmentMade(uint256 projectId, address investor, uint256 amount);
    event PropertyPurchased(uint256 projectId);
    event RefundIssued(uint256 projectId, address investor, uint256 amount);

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

        emit ProjectCreated(projectId, name, fundingGoal, newProject.deadline, msg.sender);
    }

    function investInProject(uint256 projectId) external payable {
        Project storage project = projects[projectId];
        require(block.timestamp <= project.deadline, "Funding deadline has passed");
        require(msg.value > 0, "Investment amount must be greater than zero");

        project.totalFunds += msg.value;

        if (project.contributions[msg.sender] == 0) {
            project.investors.push(msg.sender);
        }
        project.contributions[msg.sender] += msg.value;

        emit InvestmentMade(projectId, msg.sender, msg.value);
    }

    function purchaseProperty(uint256 projectId) external {
        Project storage project = projects[projectId];
        require(msg.sender == project.manager, "Only the project manager can purchase the property");
        require(project.totalFunds >= project.fundingGoal, "Funding goal not yet reached");
        require(!project.propertyPurchased, "Property has already been purchased");

        project.propertyPurchased = true;

        emit PropertyPurchased(projectId);
    }

    function issueRefund(uint256 projectId, bool forcefulCancelation) external {
        Project storage project = projects[projectId];
        if (forcefulCancelation) require(msg.sender == project.manager, "Only the project manager can forcefully cancel");
        else require(block.timestamp > project.deadline, "Funding deadline has not passed yet");
    
        require(project.totalFunds < project.fundingGoal, "Funding goal was reached; no refunds available");

        uint256 amount = project.contributions[msg.sender];
        require(amount > 0, "No contributions to refund");

        project.contributions[msg.sender] = 0;

        payable(msg.sender).transfer(amount);

        emit RefundIssued(projectId, msg.sender, amount);
    }

    function getInvestors(uint256 projectId) external view returns (address[] memory) {
        return projects[projectId].investors;
    }

    function getContribution(uint256 projectId, address investor) external view returns (uint256) {
        return projects[projectId].contributions[investor];
    }

    function getProjectById(uint256 projectId) external view returns (string memory name, uint256 fundingGoal, uint256 totalFunds, uint256 deadline, address manager,bool propertyPurchased) {
        Project storage project = projects[projectId];
        return (
            project.name,
            project.fundingGoal,
            project.totalFunds,
            project.deadline,
            project.manager,
            project.propertyPurchased
        );
    }

    function getManagedProjects() external view returns (uint256[] memory, string[] memory) {
        uint256 count = 0;

        for (uint256 i = 0; i < projectCount; i++) {
            if (projects[i].manager == msg.sender) {
                count++;
            }
        }

        uint256[] memory projectIds = new uint256[](count);
        string[] memory projectNames = new string[](count);

        uint256 index = 0;
        
        for (uint256 i = 0; i < projectCount; i++) {
            if (projects[i].manager == msg.sender) {
                projectIds[index] = i;
                projectNames[index] = projects[i].name;
                index++;
            }
        }

        return (projectIds, projectNames);
    }

    function getInvestments() external view returns (uint256[] memory, uint256[] memory) {
        uint256 count = 0;

        for (uint256 i = 0; i < projectCount; i++) {
            if (projects[i].contributions[msg.sender] > 0) {
                count++;
            }
        }

        uint256[] memory projectIds = new uint256[](count);
        uint256[] memory contributions = new uint256[](count);

        uint256 index = 0;

        for (uint256 i = 0; i < projectCount; i++) {
            if (projects[i].contributions[msg.sender] > 0) {
                projectIds[index] = i;
                contributions[index] = projects[i].contributions[msg.sender];
                index++;
            }
        }

        return (projectIds, contributions);
    }    
}