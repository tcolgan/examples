class Account(object):
    num_accounts = 0
    def __init__(self,name,balance):
        self.name = name
        self.balance = balance
        Account.num_accounts += 1
    def __del__(self):
        Account.num_accounts -= 1
    def deposit(self,amt):
        self.balance = self.balance + amt
    def withdraw(self,amt):
        self.balance = self.balance - amt
    def inquiry(self):
        return self.balance

joeAccount = Account( "joe" , 100 )
billAccount = Account( "bill" , 200 )

print( "joeAccount.name = " , joeAccount.name )
print( "billAccount.balance = " , billAccount.inquiry() )
print( "num accounts = " , Account.num_accounts )
