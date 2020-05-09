open TW;
open Belt;
open ReasonUrql.Hooks;

type t = {question: string};

[@react.component]
let make = (~id) => {
  let ({response, fetching}, _) = SurveyAnswersQuery.use(~page=1);

  <Layout>
    <div className={[Display(Flex), JustifyContent(JustifyBetween)]->make}>
      <Text className=TW.[FontSize(Text2xl), Margin(Mr4)]>
        {j|Rozwiązania|j}
      </Text>
    </div>
    {fetching
       ? <Loader />
       : (
         switch (response) {
         | Data(data) =>
           let answers =
             data##addedForms##forms
             ->Array.keep(a => a##parentId->Option.getWithDefault("") === id);

           //    switch (answers) {
           //    | Some(data) =>

           <div>
             {answers
              ->Array.mapWithIndex((i, x) => {
                  let i = (i + 1)->Js.Int.toString;
                  let answers =
                    x##questions
                    ->Array.map(a =>
                        {
                          "question": a##question,
                          "answer":
                            a##answers
                            ->Option.flatMap(x => x->Array.get(0))
                            ->Option.flatMap(a =>
                                a->Option.map(a => a##answer)
                              )
                            ->Option.flatMap(s => s),
                        }
                      );
                  Js.log(answers);
                  <div>
                    <div>
                      <Text
                        className=[
                          FontSize(TextXl),
                          Display(Block),
                          Margin(Mt4),
                          Margin(Mb8),
                        ]>
                        {j|$i. Rozwiązanie|j}
                      </Text>
                    </div>
                    {answers
                     ->Array.mapWithIndex((_, a) => {
                         <div
                           className={
                             TW.[
                               Display(Flex),
                               Padding(Py4),
                               BorderWidth(BorderB),
                             ]
                             ->TW.make
                           }>
                           <div className={TW.[Width(W64)]->TW.make}>
                             <Text> {a##question} </Text>
                           </div>
                           <div className={TW.[Width(W32)]->TW.make}>
                             <Text> " - " </Text>
                           </div>
                           <div className={TW.[Width(W64)]->TW.make}>
                             <Text>
                               {a##answer
                                ->Option.getWithDefault(
                                    "Nie udzielono odpowiedzi.",
                                  )}
                             </Text>
                           </div>
                         </div>
                       })
                     ->React.array}
                  </div>;
                })
              ->React.array}
           </div>;

         //    | None => <Text> {j|Brak rozwiazań dla tej ankiety|j} </Text>
         //    };

         | _ => React.null
         }
       )}
  </Layout>;
};