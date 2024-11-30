document.addEventListener('DOMContentLoaded', async () => {
    const MMSDK = new MetaMaskSDK.MetaMaskSDK({
      dappMetadata: {
        name: "Funding DApp",
      },
    });
  
    const ethereum = MMSDK.getProvider();
    let account;
    const contractAddress = '0xA4078ca2d41c02793181BFa4e706995f2723e607';
    const contractABI = [
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
          }
        ],
        "name": "investInProject",
        "outputs": [],
        "stateMutability": "payable",
        "type": "function"
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
        "name": "InvestmentMade",
        "type": "event"
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
      }
    ];
  
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
  
    document.getElementById('connectWallet').addEventListener('click', connectWallet);
  
    const createProject = async () => {
      const name = document.getElementById('projectName').value;
      const fundingGoal = ethereum.utils.toWei(document.getElementById('fundingGoal').value, 'ether');
      const duration = document.getElementById('duration').value;
  
      const tx = {
        to: contractAddress,
        data: contractABI.methods.createProject(name, fundingGoal, duration).encodeABI(),
      };
  
      try {
        await ethereum.request({ method: 'eth_sendTransaction', params: [tx] });
        loadManagedProjects();
      } catch (error) {
        console.error('Error creating project:', error);
      }
    };
  
    document.getElementById('createProjectBtn').addEventListener('click', createProject);
  
    const loadManagedProjects = async () => {
      // Call your smart contract method to get projects managed by the account.
      // Populate the "managedProjects" list here.
    };
  
    const investInProject = async () => {
      const projectId = document.getElementById('investProjectId').value;
      const amount = ethereum.utils.toWei(document.getElementById('investAmount').value, 'ether');
  
      const tx = {
        to: contractAddress,
        value: amount,
        data: contractABI.methods.investInProject(projectId).encodeABI(),
      };
  
      try {
        await ethereum.request({ method: 'eth_sendTransaction', params: [tx] });
        loadInvestments();
      } catch (error) {
        console.error('Error investing in project:', error);
      }
    };
  
    document.getElementById('investBtn').addEventListener('click', investInProject);
  
    const loadInvestments = async () => {
      // Call your smart contract method to get investments for the account.
      // Populate the "investedProjects" list here.
    };
  });