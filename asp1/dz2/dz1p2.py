import random as slucajan
class Node1:
    def __init__(self):
        self.info = None
        self.next = None
class Node2:
    def __init__(self):
        self.info = None
        self.next = None
        self.prev = None
class LinkedList:
    def __init__(self):
        self.pocetni_cvor = None
        self.poslednji_cvor=None
    def unos_studenata(self, y):
        if self.pocetni_cvor==None:
            novi_cvor=Node1()
            novi_cvor.info=y
            self.pocetni_cvor=novi_cvor
        else:
            trenutni_cvor=self.pocetni_cvor
            while trenutni_cvor.next!=None:
                trenutni_cvor=trenutni_cvor.next
            novi_cvor=Node1()
            novi_cvor.info=y
            trenutni_cvor.next=novi_cvor
    def broj_studenata(self):
        brojac = 0
        trenutni_cvor = self.pocetni_cvor
        while trenutni_cvor != None:
            brojac = brojac + 1
            trenutni_cvor = trenutni_cvor.next
        print('Broj studenata za upis je:',brojac)
        return brojac
    def dodavanje_red(self,brojac,lista,broj_koraka):
        while brojac>0:
            trenutni_lista = lista.pocetni_cvor
            trenlis=trenutni_lista
            student=0
            r=slucajan.randint(0,brojac-1)
            if self.pocetni_cvor==None:
                while student!=r:
                    student+=1
                    trenlis=trenutni_lista
                    if trenutni_lista.next!=None:
                        trenutni_lista=trenutni_lista.next
                novi_cvor=Node2()
                novi_cvor.info=trenutni_lista.info
                broj_koraka+=1
                self.pocetni_cvor=novi_cvor
                trenutni_red=self.pocetni_cvor
                self.poslednji_cvor=trenutni_red
                if trenutni_lista==trenlis:
                    if student==0:
                        trenutni_lista=trenutni_lista.next
                        lista.pocetni_cvor=trenutni_lista
                        del trenlis
                    elif student==brojac-1:
                        k=0
                        trenlis=lista.pocetni_cvor
                        while k!=r-1:
                            k+=1
                            trenlis=trenlis.next
                        del trenlis.next
                else:
                    trenlis.next=trenutni_lista.next
                    trenutni_lista.next=None
                    del trenutni_lista
            else:
                while student != r:
                    student += 1
                    trenlis = trenutni_lista
                    if trenutni_lista.next!=None:
                        trenutni_lista = trenutni_lista.next
                novi_cvor = Node2()
                novi_cvor.info = trenutni_lista.info
                broj_koraka+=1
                novi_cvor.prev=trenutni_red
                novi_cvor.next=None
                trenutni_red.next=novi_cvor
                trenutni_red=novi_cvor
                self.poslednji_cvor = trenutni_red
                if trenutni_lista==trenlis:
                    if student==0:
                        trenutni_lista=trenutni_lista.next
                        trenlis.next=None
                        lista.pocetni_cvor=trenutni_lista
                        del trenlis
                    elif student==brojac-1:
                        trenlis=lista.pocetni_cvor
                        while trenlis.next!=None:
                            trenlis=trenlis.next
                        del trenlis.next
                else:

                    trenlis.next=trenutni_lista.next
                    trenutni_lista.next=None
                    del trenutni_lista
            brojac-=1
        return broj_koraka
    def upis(self,broj_koraka,a):
        pocetni_red=self.pocetni_cvor
        krajnji_red=self.poslednji_cvor
        print(pocetni_red.info)
        print(krajnji_red.info)
        while pocetni_red!=krajnji_red:
            r=slucajan.random()
            if r>a:
                print(pocetni_red.info[0]+' '+pocetni_red.info[1]+', '+str(int(pocetni_red.info[4])+1))
                broj_koraka+=1
                pocetni_red=pocetni_red.next
                self.pocetni_cvor=pocetni_red
                pocetni_red.prev=None
                del pocetni_red.prev
            else:
                krajnji_red.next=pocetni_red
                pocetni_red.prev=krajnji_red
                krajnji_red=pocetni_red
                pocetni_red=pocetni_red.next
                broj_koraka+=1
        print(pocetni_red.info[0]+' '+pocetni_red.info[1]+', '+str(int(pocetni_red.info[4])+1))
        self.pocetni_cvor=None
        self.poslednji_cvor=None
        del self.pocetni_cvor
        return broj_koraka+1
    def prazan_red(self):
        if self.pocetni_cvor==None:
            print('Red je prazan!')
        else:
            print('Red nije prazan!')
    def pun_red(self,brojac):
        broj_el = 0
        trenutni_cvor = self.pocetni_cvor
        while trenutni_cvor != None:
            broj_el = broj_el + 1
            trenutni_cvor = trenutni_cvor.next
        if brojac==broj_el:
            print('Red je pun!')
        else:
            print('Red nije pun!')
    def dohvatanje_elementa(self):
        if self.pocetni_cvor!=None:
            print(self.pocetni_cvor.info);
            sledeci_cvor=self.pocetni_cvor.next
            self.pocetni_cvor=sledeci_cvor
    def stavljanje_elementa(self,info):
        if self.poslednji_cvor!=None:
            novi_cvor=Node2()
            novi_cvor.info=info
            novi_cvor.next=None
            novi_cvor.prev=self.poslednji_cvor
            self.poslednji_cvor.next=novi_cvor
            self.poslednji_cvor=novi_cvor
        else:
            novi_cvor=Node2()
            novi_cvor.info=info
            self.pocetni_cvor=novi_cvor
            self.poslednji_cvor=novi_cvor

print("1.Ucitaj podatke o studentima!\n2.Pokreni simulaciju!\n3.Prekid programa!\n")
broj_koraka=0
while True:
    try:
        x=int(input('Unesi redni broj stavke: '))
    except ValueError:
        print('Nevalidan unos stavke!')
        continue
    if x>3 or x<1:
        print('Nevalidan unos stavke!')
    elif x==1:
        ulancana = LinkedList()
        while True:
            y=input('Unesi podatke o studentu odvojene zarezom(unos praznog stringa oznacava kraj unosa) oblika (Ime, Prezime, Broj indeksa, Studijski program, Trenutna godina): ').split(',')
            if y[0]=='':
                break
            ulancana.unos_studenata(y)
        brojac=ulancana.broj_studenata()
    elif x==2:
        while True:
            try:
                a=float(input('Unesi granicu izmedju 0 i 0.5: '))
            except ValueError:
                print('Nevalidan unos')
                continue
            if a<0 or a>0.5:
                print('Losa granica!')
            else:
                break
        red=LinkedList()
        try:
            broj_koraka=red.dodavanje_red(brojac,ulancana,broj_koraka)
            try:
                broj_koraka=red.upis(broj_koraka,a)
                print('Ukupan broj koraka je: ',broj_koraka)
            except ValueError:
                print('Nevalidan unos studenta!')
            except IndexError:
                print('Nevalidan unos studenta!')
        except AttributeError:
            print('Prazan red!')
        except NameError:
            print('Prazan red!')
        broj_koraka=0
        ulancana.broj_studenata()
    elif x==3:
        break
