Loco program runner core
========================

We use this python-c library to run program in a sandbox-like environment.
With it, we can accurately known the resource using of the program and 
limit its resource using including system-call interrupt.

Usage
-----

For run a program without tracing:

    runcfg = {
        'args':['./m'],
        'fd_in':fin.fileno(),
        'fd_out':ftemp.fileno(),
        'timelimit':1000, #in MS
        'memorylimit':20000, #in KB
    }
    
    rst = lorun.run(runcfg)

For check one output:

    ftemp = file('temp.out')
    fout = file(out_path)
    crst = lorun.check(fout.fileno(), ftemp.fileno())


