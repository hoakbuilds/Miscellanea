package main

import (
	"io/ioutil"
	"log"
	"path/filepath"
	"strings"
	"time"

	"github.com/btcsuite/btcd/rpcclient"
	"github.com/btcsuite/btcutil"
)

// ConnectRPC - RPC connection to veil daemon
func ConnectRPC() {

	// Only override the handlers for notifications you care about.
	// Also note most of the handlers will only be called if you register
	// for notifications.  See the documentation of the rpcclient
	// NotificationHandlers type for more details about each handler.
	ntfnHandlers := rpcclient.NotificationHandlers{
		OnAccountBalance: func(account string, balance btcutil.Amount, confirmed bool) {
			log.Printf("New balance for account %s: %v", account,
				balance)
		},
	}

	// Connect to local btcwallet RPC server using websockets.
	certHomeDir := "/home/hugo/Desktop/simnet/btcw/"
	certs, err := ioutil.ReadFile(filepath.Join(certHomeDir, "rpc.cert"))
	if err != nil {
		log.Fatal(err)
	}

	connCfg := &rpcclient.ConnConfig{
		Host:         "localhost:18554",
		User:         "kek",
		Pass:         "kek",
		Endpoint:     "ws",
		Certificates: certs,
	}
	client, err := rpcclient.New(connCfg, &ntfnHandlers)
	if err != nil {
		log.Fatal(err)
	}

	defer client.Shutdown()

	unlockErr := client.WalletPassphrase("password", 360000)
	if unlockErr != nil {
		log.Fatal(unlockErr)
		return
	}

	amount, err := client.GetBalance("simnet")
	if err != nil {
		log.Print(err)
	} else {
		log.Printf("acc 'simnet' balance: %v", amount)
	}

	// Get the current block count.
	err = client.CreateNewAccount("lnd-bob")
	if err != nil {
		errCode := strings.Split(err.Error(), ":")
		if errCode[0] == "-4" {

			log.Printf("lnd-bob account exists.")
			prevAddr, err := client.GetAddressesByAccount("lnd-bob")
			if err != nil {
				log.Print(err)
			}

			if len(prevAddr) == 0 {
				// Get the current block count.
				address, err := client.GetNewAddress("lnd-bob")
				if err != nil {
					log.Print(err)
				} else {

					log.Printf("raw address: %d", address)
					log.Printf("new address: %s", address.EncodeAddress())
				}

			}
			log.Printf("prev address: %s", prevAddr)
		}
	}

	amount, err = client.GetBalance("lnd-bob")
	if err != nil {
		log.Print(err)
	} else {
		log.Printf("acc 'lnd-bob' balance: %v", amount)
	}

	// Get the current block count.
	err = client.CreateNewAccount("lnd-alice")
	if err != nil {
		errCode := strings.Split(err.Error(), ":")
		if errCode[0] == "-4" {
			log.Printf("lnd-alice account exists.")
			prevAddr, err := client.GetAddressesByAccount("lnd-alice")
			if err != nil {
				log.Print(err)
			}

			if len(prevAddr) == 0 {
				// Get the current block count.
				address, err := client.GetNewAddress("lnd-alice")
				if err != nil {
					log.Print(err)
				} else {

					log.Printf("raw address: %d", address)
					log.Printf("new address: %s", address.EncodeAddress())
				}

			}
			log.Printf("prev address: %s", prevAddr)
		}
	}

	amount, err = client.GetBalance("lnd-alice")
	if err != nil {
		log.Print(err)
	} else {
		log.Printf("acc 'lnd-alice' balance: %v", amount)
	}

	// Get the current block count.
	err = client.CreateNewAccount("lnd-claire")
	if err != nil {
		errCode := strings.Split(err.Error(), ":")
		if errCode[0] == "-4" {
			log.Printf("lnd-claire account exists.")
			prevAddr, err := client.GetAddressesByAccount("lnd-claire")
			if err != nil {
				log.Print(err)
			}

			if len(prevAddr) == 0 {
				// Get the current block count.
				address, err := client.GetNewAddress("lnd-claire")
				if err != nil {
					log.Print(err)
				} else {

					log.Printf("raw address: %d", address)
					log.Printf("new address: %s", address.EncodeAddress())
				}

			}
			log.Printf("prev address: %s", prevAddr)
		}

	}

	amount, err = client.GetBalance("lnd-claire")
	if err != nil {
		log.Print(err)
	} else {
		log.Printf("acc 'lnd-claire' balance: %v", amount)
	}
	/*
		// Get the current block count.
		address, err := client.GetNewAddress("simnet")
		if err != nil {
			log.Print(err)
		} else {

			log.Printf("raw address: %d", address)
			log.Printf("new address: %s", address.EncodeAddress())
		}*/
	// For this example gracefully shutdown the client after 10 seconds.
	// Ordinarily when to shutdown the client is highly application
	// specific.
	log.Println("Client shutdown in 3600 seconds...")
	time.AfterFunc(time.Second*3600, func() {
		log.Println("Client shutting down...")
		client.Shutdown()
		log.Println("Client shutdown complete.")
	})

	// Wait until the client either shuts down gracefully (or the user
	// terminates the process with Ctrl+C).
	client.WaitForShutdown()
}

// fun main()
func mainTest() {
	ConnectRPC()
}

func main() {
	mainTest()
}
