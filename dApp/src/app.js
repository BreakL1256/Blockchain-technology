import Web3 from 'web3';
import { MetaMaskSDK  } from '@metamask/sdk';  // Assuming you're using MetaMask SDK

const MMSDK = new MetaMaskSDK({
  dappMetadata: {
      name: "Example JavaScript Dapp",
      url: window.location.href,
  },
  infuraAPIKey: "https://sepolia.infura.io/v3/79785bfd30f744ba965efd1d75dcb050",
});

// Get contract address from environment variables
const contractAddress = "0xA4078ca2d41c02793181BFa4e706995f2723e607";
const contractABI = [  // This can also be moved to a separate file, if needed
  {
    "anonymous": false,
    "inputs": [
      {
        "indexed": false,
        "internalType": "uint256",
        "name": "projectId",
        "type": "uint256"
      },
      {
        "indexed": false,
        "internalType": "address",
        "name": "investor",
        "type": "address"
      },
      {
        "indexed": false,
        "internalType": "uint256",
        "name": "amount",
        "type": "uint256"
      }
    ],
    "name": "InvestmentMade",
    "type": "event"
  },
  {
    "anonymous": false,
    "inputs": [
      {
        "indexed": false,
        "internalType": "uint256",
        "name": "projectId",
        "type": "uint256"
      },
      {
        "indexed": false,
        "internalType": "string",
        "name": "name",
        "type": "string"
      },
      {
        "indexed": false,
        "internalType": "uint256",
        "name": "fundingGoal",
        "type": "uint256"
      },
      {
        "indexed": false,
        "internalType": "uint256",
        "name": "deadline",
        "type": "uint256"
      },
      {
        "indexed": false,
        "internalType": "address",
        "name": "manager",
        "type": "address"
      }
    ],
    "name": "ProjectCreated",
    "type": "event"
  },
  {
    "anonymous": false,
    "inputs": [
      {
        "indexed": false,
        "internalType": "uint256",
        "name": "projectId",
        "type": "uint256"
      }
    ],
    "name": "ProjectDeleted",
    "type": "event"
  },
  {
    "anonymous": false,
    "inputs": [
      {
        "indexed": false,
        "internalType": "uint256",
        "name": "projectId",
        "type": "uint256"
      }
    ],
    "name": "PropertyPurchased",
    "type": "event"
  },
  {
    "anonymous": false,
    "inputs": [
      {
        "indexed": false,
        "internalType": "uint256",
        "name": "projectId",
        "type": "uint256"
      },
      {
        "indexed": false,
        "internalType": "address",
        "name": "investor",
        "type": "address"
      },
      {
        "indexed": false,
        "internalType": "uint256",
        "name": "amount",
        "type": "uint256"
      }
    ],
    "name": "RefundIssued",
    "type": "event"
  },
  {
    "inputs": [
      {
        "internalType": "string",
        "name": "name",
        "type": "string"
      },
      {
        "internalType": "uint256",
        "name": "fundingGoal",
        "type": "uint256"
      },
      {
        "internalType": "uint256",
        "name": "durationInDays",
        "type": "uint256"
      }
    ],
    "name": "createProject",
    "outputs": [],
    "stateMutability": "nonpayable",
    "type": "function"
  },
  {
    "inputs": [
      {
        "internalType": "uint256",
        "name": "projectId",
        "type": "uint256"
      },
      {
        "internalType": "address",
        "name": "investor",
        "type": "address"
      }
    ],
    "name": "getContribution",
    "outputs": [
      {
        "internalType": "uint256",
        "name": "",
        "type": "uint256"
      }
    ],
    "stateMutability": "view",
    "type": "function"
  },
  {
    "inputs": [],
    "name": "getInvestments",
    "outputs": [
      {
        "internalType": "uint256[]",
        "name": "",
        "type": "uint256[]"
      },
      {
        "internalType": "uint256[]",
        "name": "",
        "type": "uint256[]"
      }
    ],
    "stateMutability": "view",
    "type": "function"
  },
  {
    "inputs": [
      {
        "internalType": "uint256",
        "name": "projectId",
        "type": "uint256"
      }
    ],
    "name": "getInvestors",
    "outputs": [
      {
        "internalType": "address[]",
        "name": "",
        "type": "address[]"
      }
    ],
    "stateMutability": "view",
    "type": "function"
  },
  {
    "inputs": [],
    "name": "getManagedProjects",
    "outputs": [
      {
        "internalType": "uint256[]",
        "name": "",
        "type": "uint256[]"
      },
      {
        "internalType": "string[]",
        "name": "",
        "type": "string[]"
      }
    ],
    "stateMutability": "view",
    "type": "function"
  },
  {
    "inputs": [
      {
        "internalType": "uint256",
        "name": "projectId",
        "type": "uint256"
      }
    ],
    "name": "getProjectById",
    "outputs": [
      {
        "internalType": "string",
        "name": "name",
        "type": "string"
      },
      {
        "internalType": "uint256",
        "name": "fundingGoal",
        "type": "uint256"
      },
      {
        "internalType": "uint256",
        "name": "totalFunds",
        "type": "uint256"
      },
      {
        "internalType": "uint256",
        "name": "deadline",
        "type": "uint256"
      },
      {
        "internalType": "address",
        "name": "manager",
        "type": "address"
      },
      {
        "internalType": "bool",
        "name": "propertyPurchased",
        "type": "bool"
      }
    ],
    "stateMutability": "view",
    "type": "function"
  },
  {
    "inputs": [
      {
        "internalType": "uint256",
        "name": "projectId",
        "type": "uint256"
      }
    ],
    "name": "investInProject",
    "outputs": [],
    "stateMutability": "payable",
    "type": "function"
  },
  {
    "inputs": [
      {
        "internalType": "uint256",
        "name": "projectId",
        "type": "uint256"
      },
      {
        "internalType": "bool",
        "name": "forcefulCancelation",
        "type": "bool"
      }
    ],
    "name": "issueRefund",
    "outputs": [],
    "stateMutability": "nonpayable",
    "type": "function"
  },
  {
    "inputs": [],
    "name": "projectCount",
    "outputs": [
      {
        "internalType": "uint256",
        "name": "",
        "type": "uint256"
      }
    ],
    "stateMutability": "view",
    "type": "function"
  },
  {
    "inputs": [
      {
        "internalType": "uint256",
        "name": "",
        "type": "uint256"
      }
    ],
    "name": "projects",
    "outputs": [
      {
        "internalType": "string",
        "name": "name",
        "type": "string"
      },
      {
        "internalType": "uint256",
        "name": "fundingGoal",
        "type": "uint256"
      },
      {
        "internalType": "uint256",
        "name": "totalFunds",
        "type": "uint256"
      },
      {
        "internalType": "uint256",
        "name": "deadline",
        "type": "uint256"
      },
      {
        "internalType": "address",
        "name": "manager",
        "type": "address"
      },
      {
        "internalType": "bool",
        "name": "propertyPurchased",
        "type": "bool"
      }
    ],
    "stateMutability": "view",
    "type": "function"
  },
  {
    "inputs": [
      {
        "internalType": "uint256",
        "name": "projectId",
        "type": "uint256"
      }
    ],
    "name": "purchaseProperty",
    "outputs": [],
    "stateMutability": "nonpayable",
    "type": "function"
  }
];

let contract;
let account;
let investedProjects = [];

document.addEventListener('DOMContentLoaded', async () => {
    const ethereum = MMSDK.getProvider(); // Use the provider from MetaMask SDK
    const web3 = new Web3(ethereum); // Set up Web3 with the provider from MetaMask
    contract = new web3.eth.Contract(contractABI, contractAddress);

    // Function to connect wallet
    const connectWallet = async () => {
        if (!ethereum) {
            alert('MetaMask is not installed!');
            return;
        }

        try {
            const accounts = await ethereum.request({ method: 'eth_requestAccounts' });
            account = accounts[0];
            document.getElementById('walletAddress').innerText = `Connected: ${account}`;
            await loadManagedProjects();
            await populateProjectDropdown();
            await loadOwnInvestments();
            await loadInvestments();
        } catch (error) {
            console.error('Error connecting wallet:', error);
        }
    };

    // Event listener for the connect wallet button
    // document.getElementById('connectWallet').addEventListener('click', connectWallet);

    // Function to create a project
    const createProject = async () => {
        const name = document.getElementById('projectName').value;
        const fundingGoal = document.getElementById('fundingGoal').value;
        const duration = document.getElementById('duration').value;

        try {
            await contract.methods
                .createProject(name, web3.utils.toWei(fundingGoal, 'ether'), duration)
                .send({ from: account });
            alert('Project created successfully!');
            populateProjectDropdown();
            loadManagedProjects();
        } catch (error) {
            console.error('Error creating project:', error);
        }
    };

    // Event listener for the create project button
    document.getElementById('createProjectBtn').addEventListener('click', createProject);

    // Function to load managed projects
    const loadManagedProjects = async () => {
        try {
            const allObjects = await contract.methods.getManagedProjects().call({ from: account });

            const projectIds = allObjects[0];
            const projectNames = allObjects[1];

            if(projectIds && projectNames){
              console.log(projectIds, projectNames);
              const list = document.getElementById('managedProjects');
              list.innerHTML = '';
              projectIds.forEach((id, index) => {
                  const item = document.createElement('li');
                  item.innerText = `${projectNames[index]} (ID: ${id})`;
                  list.appendChild(item);
              });
          }
        } catch (error) {
            console.error('Error loading managed projects:', error);
        }
    };

    const loadOwnInvestments = async () => {
      try {
          investedProjects = [];

          const projectCount = await contract.methods.projectCount().call({ from: account });
          for(let i=0; i<projectCount; i++){
            const investors = await contract.methods.getInvestors(i).call({ from: account });
            for(let j=0; j<investors.length; j++){
              if(investors[j].toLowerCase() == account.toLowerCase()) {
                const projectDetails = await contract.methods.getProjectById(i).call({ from: account });
                investedProjects.push(projectDetails);
              }
            }
          }
      } catch (error) {
          console.error('Error loading managed projects:', error);
      }
  };

    // Function to invest in a project
    const investInProject = async () => {
        const projectId = document.getElementById('investProjectId').value;
        const amount = document.getElementById('investAmount').value;
        
        try {
            await contract.methods.investInProject(projectId).send({
                from: account,
                value: web3.utils.toWei(amount, 'ether'),
            });
            alert('Investment successful!');
            await loadOwnInvestments();
            await loadInvestments();
        } catch (error) {
            console.error('Error investing in project:', error);
        }
    };

    // Event listener for the invest button
    document.getElementById('investBtn').addEventListener('click', investInProject);

    // Function to load investments
    const loadInvestments = async () => {
      try {
          console.log(investedProjects);
          const container = document.getElementById('investedProjects');
          container.innerHTML = ''; // Clear previous investments

          investedProjects.forEach((project) => {
              // Create a card for each investment
              const card = document.createElement('div');
              card.classList.add('investment-card');

              // Add project details
              card.innerHTML = `
                  <h4>${project.name}</h4>
                  <p>Funding Goal: ${project.fundingGoal} ETH</p>
                  <p>Collected Funds: ${project.totalFunds} ETH</p>
                  <p>Manager: ${project.manager}</p>
                  <div class="progress-container">
                      <div class="progress-bar" style="width: ${
                        (project.totalFunds / project.fundingGoal) * 100
                      }%;"></div>
                  </div>
                  <p class="progress-text">${project.totalFunds} / ${project.fundingGoal} ETH</p>
              `;

              container.appendChild(card);
          });
      } catch (error) {
          console.error('Error loading investments:', error);
      }
    };

    // Populate the project selection dropdown for investments
    const populateProjectDropdown = async () => {
        try {
            const projectCount = await contract.methods.projectCount().call({ from: account });

            if(projectCount){
              const dropdown = document.getElementById('investProjectId');
              dropdown.innerHTML = '';
              for(let i=0; i<projectCount; i++){
                const projectDetails = await contract.methods.projects(i).call({ from: account });
                const option = document.createElement('option');
                option.value = i;
                option.innerText = `funding goal: ${projectDetails.fundingGoal} || manager: ${projectDetails.manager}`;
                dropdown.appendChild(option);
              }
            }
        } catch (error) {
            console.error('Error populating project dropdown:', error);
        }
    };

  //   const getProject = async (projectId) => {
  //     try {
  //         // Call the `getProjectById` function from the contract
  //         const projectDetails = await contract.methods.getProjectById(projectId).call({ from: account });
  
  //         console.log("Project Details:");
  //         console.log("Name:", projectDetails.name);
  //         console.log("Funding Goal:", projectDetails.fundingGoal);
  //         console.log("Total Funds:", projectDetails.totalFunds);
  //         console.log("Deadline:", projectDetails.deadline);
  //         console.log("Manager:", projectDetails.manager);
  //         console.log("Property Purchased:", projectDetails.propertyPurchased);
  //     } catch (error) {
  //         console.error("Error fetching project details:", error);
  //     }
  // };

    // Call necessary functions on wallet connection
    connectWallet();

    // getProject(0);

});