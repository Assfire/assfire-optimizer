# assfire-optimizer

This repo is a part of the in-development route optimizaton services collection (https://github.com/Eaglegor/assfire-suite). The intention of this repo is to step out of monorepo development model and move to more flexible model of per-service repo.

This service is intended to provide algorithms for solving route optimization tasks such as TSP (Travelling Salesmna Problem) and VRP (Vehicle routing problem). It will be based on my previous works (https://github.com/Eaglegor/SchedulerEngine and https://github.com/Eaglegor/assfire-suite/tree/master/apps/tsp).

As many of Assfire components, this component may be used as a library ('engine' module) or as a standalone service ('client' and 'server' modules). Both client and engine implement same api ('api' module) for better interchangeability.