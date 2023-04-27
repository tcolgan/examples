import logging

logging.basicConfig(
  filename = "app.log",
  format = "%(levelname)-10s %(asctime)s %(message)s" ,
  level = logging.INFO
)


log = logging.getLogger('app')

#log.critical("Tim's test")
#log.error   ("Tim's test")
log.warning ("Tim's test")
#log.info    ("Tim's test")
#log.debug   ("Tim's test")
