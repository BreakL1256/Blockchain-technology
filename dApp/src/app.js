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

document.addEventListener('DOMContentLoaded', async () => {
    const ethereum = MMSDK.getProvider(); // Use the provider from MetaMask SDK
    const web3 = new Web3(ethereum); // Set up Web3 with the provider from MetaMask
    const contract = new web3.eth.Contract(contractABI, contractAddress);
    let account;

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
            loadManagedProjects();
            loadInvestments();
        } catch (error) {
            console.error('Error connecting wallet:', error);
        }
    };

    // Event listener for the connect wallet button
    document.getElementById('connectWallet').addEventListener('click', connectWallet);

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
            const { projectIds, projectNames } = await contract.methods.getManagedProjects().call({ from: account });
            const list = document.getElementById('managedProjects');
            list.innerHTML = '';
            projectIds.forEach((id, index) => {
                const item = document.createElement('li');
                item.innerText = `${projectNames[index]} (ID: ${id})`;
                list.appendChild(item);
            });
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
            loadInvestments();
        } catch (error) {
            console.error('Error investing in project:', error);
        }
    };

    // Event listener for the invest button
    document.getElementById('investBtn').addEventListener('click', investInProject);

    // Function to load investments
    const loadInvestments = async () => {
        try {
            const { projectIds, contributions } = await contract.methods.getInvestments().call({ from: account });
            const list = document.getElementById('investedProjects');
            list.innerHTML = '';
            projectIds.forEach((id, index) => {
                const item = document.createElement('li');
                item.innerText = `Project ID: ${id}, Contribution: ${web3.utils.fromWei(contributions[index], 'ether')} ETH`;
                list.appendChild(item);
            });
        } catch (error) {
            console.error('Error loading investments:', error);
        }
    };

    // Populate the project selection dropdown for investments
    const populateProjectDropdown = async () => {
        try {
            const { projectIds, projectNames } = await contract.methods.getManagedProjects().call({ from: account });
            const dropdown = document.getElementById('investProjectId');
            dropdown.innerHTML = '';
            projectIds.forEach((id, index) => {
                const option = document.createElement('option');
                option.value = id;
                option.innerText = projectNames[index];
                dropdown.appendChild(option);
            });
        } catch (error) {
            console.error('Error populating project dropdown:', error);
        }
    };

    // Call necessary functions on wallet connection
    connectWallet();
});