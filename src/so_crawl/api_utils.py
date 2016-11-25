from datetime import datetime

BASE_URL = 'http://api.stackexchange.com/2.2'
COMMON_WRAPPER_FIELDS = frozenset([
    ".has_more",
    ".items",
    ".quota_max",
    ".quota_remaining"
])
MAX_PAGE_SIZE = 100  # Limit set by stackexchange API
ANSWER_BATCH_SIZE = 100  # Limit set by stackexchange API


def augment_api_fields(fields):
    all_fields = set(COMMON_WRAPPER_FIELDS)
    all_fields.update(fields)
    return all_fields


def seconds_since_epoch(datetime_value):
    epoch = datetime(1970, 1, 1)
    seconds = (datetime_value - epoch).total_seconds()
    return long(seconds)


def build_url(entity, **kwargs):
    arg_array = []
    for arg_name, value in kwargs.iteritems():
        if not value:
            continue
        if isinstance(value, datetime):
            final_value = seconds_since_epoch(value)
        elif isinstance(value, basestring):
            final_value = str(value)
        else:
            try:
                iter(value)
                final_value = ';'.join([str(v) for v in value])
            except TypeError:
                final_value = str(value)
        arg_array.append('{}={}'.format(arg_name, final_value))

    arg_string = '&'.join(sorted(arg_array))
    url = '{}/{}?{}'.format(BASE_URL, entity, arg_string)
    return url
