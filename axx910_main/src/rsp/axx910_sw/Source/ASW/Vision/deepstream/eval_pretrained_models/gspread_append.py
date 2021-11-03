
import sys
import gspread
from parse_stats import parse_stats

sheet_name = sys.argv[1]
perf = sys.argv[2]
gpu_usage = sys.argv[3]
output_file_uri = sys.argv[4]

gc = gspread.oauth()

sh_key = '1HvhCXSIDR8Auhw_zH42oJbpEomWFGDE4RbGYKrOUJR8'
wks_name = sheet_name


sh = gc.open_by_key(sh_key)


try:
    wks = sh.worksheet(wks_name)
except gspread.exceptions.WorksheetNotFound:
    sh.add_worksheet(wks_name, rows="100", cols="20")
    wks = sh.worksheet(wks_name)




worst_perf, avg_gpu_usage = parse_stats(perf, gpu_usage)
wks.append_row([perf.split('_perf')[0], int(worst_perf), int(avg_gpu_usage), output_file_uri], table_range='A1')    
