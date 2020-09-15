from time import time, sleep

import Farm_Evaluator as eval_normal
import Farm_Evaluator_Vec as eval_vec

# The specification of the turbines
TURBINE_SPECS = {
    'Name': 'Anon Name',
    'Vendor': 'Anon Vendor',
    'Type': 'Anon Type',
    'Dia (m)': 100,
    'Rotor Area (m2)': 7853,
    'Hub Height (m)': 100,
    'Cut-in Wind Speed (m/s)': 3.5,
    'Cut-out Wind Speed (m/s)': 25,
    'Rated Wind Speed (m/s)': 15,
    'Rated Power (MW)': 3
}

# The amount of runs to run each evaluator
RUNS = 100

def benchmark(func):
    start = time()

    for i in range(RUNS):
        func()

    end = time()
    return RUNS / (end - start)

def prepare_normal():
    turbine_diameter = TURBINE_SPECS['Dia (m)']

    # Turbine x,y coordinates
    turbine_coordinates = eval_normal.getTurbLoc(r'../data/turbine_loc_test.csv')
    power_curve = eval_normal.loadPowerCurve(r'../data/power_curve.csv')
    wind_inst_freq = eval_normal.binWindResourceData(r'../data/wind/wind_data_2007.csv')

    return {
        'turbine_diameter': turbine_diameter,
        'turbine_coordinates': turbine_coordinates,
        'power_curve': power_curve,
        'wind_inst_freq': wind_inst_freq
    }

def run_normal(ctx):
    eval_normal.totalAEP(
        ctx['turbine_diameter'],
        ctx['turbine_coordinates'],
        ctx['power_curve'],
        ctx['wind_inst_freq']
    )

def prepare_vec():
    turbine_diameter = TURBINE_SPECS['Dia (m)']
    turbine_radius = turbine_diameter / 2

    turbine_coordinates = eval_vec.getTurbLoc(r'../data/turbine_loc_test.csv')
    power_curve = eval_vec.loadPowerCurve(r'../data/power_curve.csv')
    wind_inst_freq = eval_vec.binWindResourceData(r'../data/wind/wind_data_2007.csv')

    n_wind_instances, cos_dir, sin_dir, wind_sped_stacked, C_t = eval_vec.preProcessing(power_curve)

    return {
        'turbine_radius': turbine_radius,
        'turbine_coordinates': turbine_coordinates,
        'power_curve': power_curve,
        'wind_inst_freq': wind_inst_freq,
        'n_wind_instances': n_wind_instances,
        'cos_dir': cos_dir,
        'sin_dir': sin_dir,
        'wind_sped_stacked': wind_sped_stacked,
        'C_t': C_t
    }

def run_vec(ctx):
    eval_vec.getAEP(
        ctx['turbine_radius'],
        ctx['turbine_coordinates'],
        ctx['power_curve'],
        ctx['wind_inst_freq'],
        ctx['n_wind_instances'],
        ctx['cos_dir'],
        ctx['sin_dir'],
        ctx['wind_sped_stacked'],
        ctx['C_t']
    )

if __name__ == '__main__':
    print('Preparing the normal evaluator')
    normal_ctx = prepare_normal()

    print(f'Running the normal evaluator {RUNS} times, this may take a while')
    normal_per_second = benchmark(lambda: run_normal(normal_ctx))

    print('Preparing the vectorized evaluator')
    vec_ctx = prepare_vec()

    print(f'Running the vectorized evaluator {RUNS} times, this may take a while')
    vec_per_second = benchmark(lambda: run_vec(vec_ctx))

    print(f'Normal runs per second: {normal_per_second:.2f}')
    print(f'Vectorized runs per second: {vec_per_second:.2f}')
