class Node:
    def __init__(self):
        self.info = None
        self.next = None
        self.prev = None
class LinkedList:
    def __init__(self):
        self.pocetni_cvor = None
    def ispis(self):
        trenutni_cvor = self.pocetni_cvor
        if trenutni_cvor==None:
            return
        if trenutni_cvor.next!=None:
            while trenutni_cvor != None:
                print(trenutni_cvor.info,end='->')
                trenutni_cvor = trenutni_cvor.next
                if trenutni_cvor.next==None:
                    break
        print(trenutni_cvor.info)
    def kardinalnost(self):
        brojac = 0
        trenutni_cvor = self.pocetni_cvor
        while trenutni_cvor != None:
            brojac = brojac + 1
            trenutni_cvor = trenutni_cvor.next
        print('Broj clanova skupa je: ',brojac)
    def pripadnost(self, info):
        trenutni_cvor = self.pocetni_cvor
        while trenutni_cvor != None:
            if trenutni_cvor.info == info:
                print('Pripada!')
                break
            elif info > trenutni_cvor.info:
                trenutni_cvor = trenutni_cvor.next
                continue
            elif info<trenutni_cvor.info:
                print('Ne pripada!')
                break
        if trenutni_cvor==None:
            print('Ne pripada')
    def brisanje(self, info):
        trenutni_cvor = self.pocetni_cvor
        if trenutni_cvor==None:
            return
        if trenutni_cvor.next!=None:
            while trenutni_cvor != None:
                if trenutni_cvor.info < info:
                    trenutni_cvor = trenutni_cvor.next
                    continue
                elif trenutni_cvor.info > info:
                    break
                elif trenutni_cvor.info==info:
                    if trenutni_cvor.prev != None and trenutni_cvor.next != None:
                        trenutni_cvor.prev.next = trenutni_cvor.next
                        trenutni_cvor.next.prev = trenutni_cvor.prev
                        trenutni_cvor.next=None
                        trenutni_cvor.prev=None
                    elif trenutni_cvor.prev == None:
                        self.pocetni_cvor = trenutni_cvor.next
                        trenutni_cvor.next.prev = None
                    elif trenutni_cvor.next == None:
                        trenutni_cvor.prev.next = None
                    break
        else:
            if info==self.pocetni_cvor.info:
                self.pocetni_cvor=None
        del trenutni_cvor
    def upis(self, info):
        if self.pocetni_cvor == None:
            novi_cvor = Node()
            novi_cvor.info = info
            self.pocetni_cvor = novi_cvor
        elif self.pocetni_cvor.info > info:
            novi_cvor = Node()
            novi_cvor.info = info
            novi_cvor.next = self.pocetni_cvor
            novi_cvor.next.prev = novi_cvor
            self.pocetni_cvor = novi_cvor
        elif self.pocetni_cvor.info < info:
            trenutni_cvor = self.pocetni_cvor
            while trenutni_cvor.next != None and trenutni_cvor.next.info < info:
                trenutni_cvor = trenutni_cvor.next
            if trenutni_cvor.next!=None and trenutni_cvor.next.info!=info:
                novi_cvor = Node()
                novi_cvor.info = info
                novi_cvor.next = trenutni_cvor.next
                novi_cvor.prev = trenutni_cvor
                trenutni_cvor.next.prev=novi_cvor
                trenutni_cvor.next = novi_cvor
            elif trenutni_cvor.next==None:
                novi_cvor = Node()
                novi_cvor.info = info
                novi_cvor.next = trenutni_cvor.next
                novi_cvor.prev = trenutni_cvor
                trenutni_cvor.next = novi_cvor
    def unija(self,x,y):
        trnx=x.pocetni_cvor
        trny=y.pocetni_cvor
        while trnx!=None and trny!=None:
            if trnx.info<trny.info:
                if self.pocetni_cvor==None:
                    novi_cvor = Node()
                    novi_cvor.info = trnx.info
                    self.pocetni_cvor = novi_cvor
                    trenutni_cvor = self.pocetni_cvor
                else:
                    novi_cvor = Node()
                    novi_cvor.info = trnx.info
                    novi_cvor.prev = trenutni_cvor
                    trenutni_cvor.next = novi_cvor
                    trenutni_cvor = novi_cvor
                trnx=trnx.next
            elif trnx.info==trny.info:
                if self.pocetni_cvor==None:
                    novi_cvor = Node()
                    novi_cvor.info = trnx.info
                    self.pocetni_cvor = novi_cvor
                    trenutni_cvor = self.pocetni_cvor
                else:
                    novi_cvor = Node()
                    novi_cvor.info = trnx.info
                    novi_cvor.prev = trenutni_cvor
                    trenutni_cvor.next = novi_cvor
                    trenutni_cvor = novi_cvor
                trnx=trnx.next
                trny=trny.next
            else:
                if self.pocetni_cvor==None:
                    novi_cvor = Node()
                    novi_cvor.info = trny.info
                    self.pocetni_cvor = novi_cvor
                    trenutni_cvor = self.pocetni_cvor
                else:
                    novi_cvor = Node()
                    novi_cvor.info = trny.info
                    novi_cvor.prev = trenutni_cvor
                    trenutni_cvor.next = novi_cvor
                    trenutni_cvor = novi_cvor
                trny=trny.next
        if trny==None and trnx!=None:
            while trnx!=None:
                if self.pocetni_cvor==None:
                    novi_cvor = Node()
                    novi_cvor.info = trnx.info
                    novi_cvor.prev=None
                    novi_cvor.next=None
                    self.pocetni_cvor=novi_cvor
                    trenutni_cvor=self.pocetni_cvor
                    trnx=trnx.next
                else:
                    novi_cvor = Node()
                    novi_cvor.info = trnx.info
                    novi_cvor.prev = trenutni_cvor
                    trenutni_cvor.next = novi_cvor
                    trenutni_cvor = novi_cvor
                    trnx=trnx.next
        elif trnx==None and trny!=None:
            while trny!=None:
                if self.pocetni_cvor==None:
                    novi_cvor = Node()
                    novi_cvor.info = trny.info
                    novi_cvor.prev=None
                    novi_cvor.next=None
                    self.pocetni_cvor=novi_cvor
                    trenutni_cvor=self.pocetni_cvor
                    trny=trny.next
                else:
                    novi_cvor = Node()
                    novi_cvor.info = trny.info
                    novi_cvor.prev = trenutni_cvor
                    trenutni_cvor.next = novi_cvor
                    trenutni_cvor = novi_cvor
                    trny=trny.next
    def razlika(self, x, y):
        trnx = x.pocetni_cvor
        trny=y.pocetni_cvor
        while trnx!=None and trny!=None:
            if trnx.info<trny.info:
                if self.pocetni_cvor == None:
                    novi_cvor = Node()
                    novi_cvor.info = trnx.info
                    self.pocetni_cvor = novi_cvor
                    trenutni_cvor = self.pocetni_cvor
                else:
                    novi_cvor = Node()
                    novi_cvor.info = trnx.info
                    novi_cvor.prev = trenutni_cvor
                    trenutni_cvor.next = novi_cvor
                    trenutni_cvor = novi_cvor
                trnx=trnx.next
            elif trnx.info>trny.info:
                trny=trny.next
            else:
                trnx=trnx.next
                trny=trny.next
        if trny==None and trnx!=None:
            while trnx!=None:
                if self.pocetni_cvor==None:
                    novi_cvor = Node()
                    novi_cvor.info = trnx.info
                    novi_cvor.next=None
                    novi_cvor.prev=None
                    self.pocetni_cvor=novi_cvor
                    trenutni_cvor=self.pocetni_cvor
                    trnx=trnx.next
                else:
                    novi_cvor = Node()
                    novi_cvor.info = trnx.info
                    novi_cvor.prev = trenutni_cvor
                    trenutni_cvor.next = novi_cvor
                    trenutni_cvor = novi_cvor
                    trnx=trnx.next
    def presek(self, x, y):
        trnx = x.pocetni_cvor
        trny = y.pocetni_cvor

        while trnx != None and trny != None:
            if trnx.info==trny.info:
                if self.pocetni_cvor==None:
                    novi_cvor=Node()
                    novi_cvor.info=trnx.info
                    self.pocetni_cvor=novi_cvor
                    trenutni_cvor=self.pocetni_cvor
                else:
                    novi_cvor=Node()
                    novi_cvor.info=trnx.info
                    novi_cvor.prev=trenutni_cvor
                    trenutni_cvor.next=novi_cvor
                    trenutni_cvor=novi_cvor
                trnx=trnx.next
                trny=trny.next
            elif trnx.info>trny.info:
                trny=trny.next
            elif trny.info>trnx.info:
                trnx=trnx.next

print("1.Ucitaj novi skup!\n2.Dodaj element u skup!\n3.Obrisi element skupa!\n4.Ispisi zadati skup!\n"
      "5.Proveri pripadnost elementa!\n6.Proveri kardinalnost skupa!\n7.Nadji uniju 2 skupa!\n8.Nadji presek 2 skupa!\n"
      "9.Nadji razliku 2 skupa!\n10.Obrisi zadati skup!\n11.Prekid programa!")
counter = 0
lista=[]
while True:
    try:
        x = int(input("Unesi stavku: "))
    except ValueError:
        print('Nevalidan unos!')
        continue
    if x>11 or x<1:
        print('Nevalidan unos stavke!')
    elif x == 1:
        skup=input("Unesi ime skupa: ")
        if skup not in lista:
            lista.append(skup)
            counter = counter + 1
            if counter > 5:
                print("Nije moguce sprovesti akciju!")
                counter=counter-1
                lista.remove(skup)
            else:
                globals()[skup]=LinkedList()
        else:
            print('Takav skup vec postoji!')
    elif x == 2:
        upis=input('Unesi skup i element oblika (naziv_skupa,element): ' ).split(',')
        try:
            globals()[upis[0]].upis(int(upis[1]))
        except KeyError:
            print('Ne postoji takav skup!')
        except ValueError:
            print('Nevalidan unos elementa!')
        except IndexError:
            print('Nevalidan unos!')
    elif x == 3:
        brisanje=input('Unesi skup i element oblika (naziv_skupa,element): ' ).split(',')
        try:
            globals()[brisanje[0]].brisanje(int(brisanje[1]))
        except KeyError:
            print('Ne postoji takav skup!')
        except ValueError:
            print('Nevalidan unos elementa!')
        except IndexError:
            print('Nevalidan unos!')
    elif x == 4:
        ispis=input('Unesi naziv skupa: ' )
        try:
            globals()[ispis].ispis()
        except KeyError:
            print('Ne postoji takav skup!')
    elif x == 5:
        pripadnost=input('Unesi skup i element oblika (naziv_skupa,element): ' ).split(',')
        try:
            globals()[pripadnost[0]].pripadnost(int(pripadnost[1]))
        except KeyError:
            print('Ne postoji takav skup!')
        except ValueError:
            print('Nevalidan unos elementa!')
        except IndexError:
            print('Nevalidan unos!')
    elif x == 6:
        kardinalnost=input('Unesi naziv skupa: ' )
        try:
            globals()[kardinalnost].kardinalnost()
        except KeyError:
            print('Ne postoji takav skup!')
    elif x == 7:
        unija=input('Unesi 2 skupa od kojih se trazi unija i 1 skup u koji se smesta unija oblika (skup1,skup2,skup3): ' ).split(',')
        try:
            globals()[unija[2]].unija(globals()[unija[0]], globals()[unija[1]])
        except KeyError:
            print('Ne postoji takav skup!')
        except IndexError:
            print('Nevalidan unos!')
        except UnboundLocalError:
            print('Moras ucitati novi skup!')
    elif x == 8:
        presek=input('Unesi 2 skupa od kojih se trazi presek i 1 skup u koji se smesta presek oblika (skup1,skup2,skup3): ' ).split(',')
        try:
            globals()[presek[2]].presek(globals()[presek[0]], globals()[presek[1]])
        except KeyError:
            print('Ne postoji takav skup!')
        except IndexError:
            print('Nevalidan unos!')
        except UnboundLocalError:
            print('Moras ucitati novi skup!')
    elif x == 9:
        razlika=input('Unesi 2 skupa od kojih se trazi razlika (prvi/drugi) i 1 skup u koji se smesta razlika oblika (skup1,skup2,skup3): ' ).split(',')
        try:
            globals()[razlika[2]].razlika(globals()[razlika[0]], globals()[razlika[1]])
        except KeyError:
            print('Ne postoji takav skup!')
        except IndexError:
            print('Nevalidan unos!')
        except UnboundLocalError:
            print('Moras ucitati novi skup!')
    elif x==10:
        brisanje_skupa=input('Unesi naziv skupa: ')
        try:
            del globals()[brisanje_skupa]
            lista.remove(brisanje_skupa)
        except KeyError:
            print('Ne postoji takav skup!')
            continue
        counter=counter-1
    elif x == 11:
        break
