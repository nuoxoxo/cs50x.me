-----------------------
--The THIEF is: Ernest
-----------------------

--------------------------------------------------------------------
---Cmds <.table> and <.schema table_name> are used at every step.---
--------------------------------------------------------------------

--On July 28, 2020, the suspect made a phonecall that matches a witness' account
--Raymond (witness no.3) said that the thief, upon exiting, called someone and talked for < 1 min

select name from people
inner join phone_calls
on people.phone_number = phone_calls.caller
where day = 28 and month = 7 and year = 2020 and duration < 60
and name in (

--Suspect's name is on the list of pax of a flight that leaves the next day of the theft
--Raymond said the thief planned to leave town on the earliest flight the next day, i.e. July 29, '20

select name from people
inner join passengers
on people.passport_number = passengers.passport_number
where flight_id = (
select flights.id from flights where day = 29 and month = 7 and year = 2020
order by hour asc limit 1)
) and people.license_plate in (

--Suspect left the courthouse at a specific time frame
--Ruth (witness no.1) mentined the thief left on a car within 10min of theft

select courthouse_security_logs.license_plate from courthouse_security_logs
where day = 28 and month = 7 and year = 2020 and hour = 10 and minute < 26 and minute > 15 )
and people.id in (

--Withdrawal was made by the suspect using the Fifer street ATM
--Eugene (witness no.2) said he saw the thief withdrew money at the ATM on Fifer Street earlier that morning

select bank_accounts.person_id from bank_accounts
where bank_accounts.account_number in (
select account_number from atm_transactions
where day = 28 and month = 7 and year = 2020 and transaction_type = 'withdraw' and atm_location = 'Fifer Street')
)


------------------------------
--The ACCOMPLICE is: Berthold
------------------------------

select name from people
inner join phone_calls
on people.phone_number = phone_calls.receiver
where day = 28 and month = 7 and year = 2020 and duration < 61 and caller = (
select people.phone_number from people
where name = (

select name from people
inner join phone_calls
on people.phone_number = phone_calls.caller
where day = 28 and month = 7 and year = 2020 and duration < 60
and name in (

select name from people
inner join passengers
on people.passport_number = passengers.passport_number
where flight_id = (

select flights.id from flights
where day = 29 and month = 7 and year = 2020 order by hour asc limit 1))
and people.license_plate in (

select courthouse_security_logs.license_plate from courthouse_security_logs
where day = 28 and month = 7 and year = 2020 and hour = 10 and minute < 26 and minute > 15 )
and people.id in (

select bank_accounts.person_id from bank_accounts
where bank_accounts.account_number in (

select account_number from atm_transactions
where day = 28 and month=7 and year = 2020 and transaction_type = 'withdraw' and atm_location = 'Fifer Street'))))


-----------------------
--The thief ESCAPED TO:
-----------------------

select city from airports
inner join flights
on airports.id = destination_airport_id
where flights.id = (
select flights.id from flights
where day = 29 and month = 7 and year = 2020
order by hour asc limit 1)
